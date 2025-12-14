/***************************************************************
 * main_uart_servo_sensor.c
 * - UART0 (EMIO) revisado cada 1ms
 * - Sensor RCWL revisado cada 5 segundos
 * - Servo controlado por AXI_GPIO_2
 ***************************************************************/

#include "xparameters.h"
#include "xuartps.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "sleep.h"
#include <string.h>

/* --------------------- DEFINES --------------------- */
/* UART0 (EMIO) */
#define UART0_BASEADDR   XPAR_XUARTPS_0_BASEADDR
#define UART0_CLK        XPAR_UART0_CLOCK_FREQ
#define UART_BAUDRATE    9600

/* AXI GPIO del SERVO */
#define GPIO_SERVO_BASEADDR   XPAR_XGPIO_2_BASEADDR

/* AXI GPIO del SENSOR RCWL-0516 */
#define GPIO_SENSOR_BASEADDR  XPAR_XGPIO_1_BASEADDR

/* Servo pulse (microsegundos) */
#define SERVO_PULSE_0US       1000
#define SERVO_PULSE_180US     2000
#define SERVO_HOLD_CYCLES     50

/* ------------------ Periféricos ------------------ */
XUartPs uart;
XGpio gpio_servo;
XGpio gpio_sensor;

/* ------------------ Funciones del SERVO ------------------ */

void pwm_pulse_us(unsigned int high_us) {
    XGpio_DiscreteWrite(&gpio_servo, 1, 1); // HIGH
    usleep(high_us);
    XGpio_DiscreteWrite(&gpio_servo, 1, 0); // LOW
    usleep(20000 - high_us);
}

void servo_hold_us(unsigned int pulse_us, unsigned int cycles) {
    for (unsigned int i = 0; i < cycles; i++) {
        pwm_pulse_us(pulse_us);
    }
}

void servo_to_0(void) {
    servo_hold_us(SERVO_PULSE_0US, SERVO_HOLD_CYCLES);
}

void servo_to_180(void) {
    servo_hold_us(SERVO_PULSE_180US, SERVO_HOLD_CYCLES);
}

/* Acción completa */
void activar_servo_evento(void) {
    xil_printf("Activando servo 180°...\r\n");
    servo_to_180();
    usleep(200000);  // pausa opcional
    xil_printf("Regresando servo a 0°...\r\n");
    servo_to_0();
}

/* ------------------ UART ------------------ */
int uart0_init(u32 baseaddr, u32 input_clk_hz, int baud)
{
    XUartPs_Config config;
    config.BaseAddress  = baseaddr;
    config.InputClockHz = input_clk_hz;

    int st = XUartPs_CfgInitialize(&uart, &config, config.BaseAddress);
    if (st != XST_SUCCESS) return -1;

    XUartPs_SetBaudRate(&uart, baud);
    return 0;
}

/* ------------------ MAIN ------------------ */
int main(void)
{
    /* SERVO GPIO */
    if (XGpio_Initialize(&gpio_servo, GPIO_SERVO_BASEADDR) != XST_SUCCESS) {
        xil_printf("Error inicializando GPIO del servo\r\n");
        return -1;
    }
    XGpio_SetDataDirection(&gpio_servo, 1, 0x0);

    /* SENSOR GPIO */
    if (XGpio_Initialize(&gpio_sensor, GPIO_SENSOR_BASEADDR) != XST_SUCCESS) {
        xil_printf("Error inicializando GPIO del sensor\r\n");
        return -1;
    }
    XGpio_SetDataDirection(&gpio_sensor, 1, 0xFFFFFFFF); // entrada

    /* UART0 */
    if (uart0_init(UART0_BASEADDR, UART0_CLK, UART_BAUDRATE) != 0) {
        xil_printf("Error inicializando UART0\r\n");
        return -1;
    }

    xil_printf("Sistema listo. Servo a 0°...\r\n");
    servo_to_0();

    /* ----------- CONTROL DE TIEMPOS ----------- */
    int contador_uart = 0;     // cada 1ms
    int contador_sensor = 0;   // cada 5000ms (5s)

    /* ----------- LOOP PRINCIPAL ----------- */
    while (1) {

        /* ---------------- UART cada 1ms ---------------- */
        if (contador_uart >= 1) {
            contador_uart = 0;

            if (XUartPs_IsReceiveData(UART0_BASEADDR)) {
                char c = XUartPs_RecvByte(UART0_BASEADDR);

                if (c == '1') {
                    xil_printf("[UART] Recibido '1'. Activando servo...\r\n");
                    activar_servo_evento();
                }
            }
        }

        /* ---------------- SENSOR cada 5s ---------------- */
        if (contador_sensor >= 5000) {
            contador_sensor = 0;

            u32 sensor_value = XGpio_DiscreteRead(&gpio_sensor, 1);

            if (sensor_value == 1) {
                xil_printf("[SENSOR] Movimiento detectado!\r\n");
                activar_servo_evento();
            }
        }

        /* ---- Delay base: 1ms para marcar el tiempo ---- */
        usleep(1000);  // 1 ms

        contador_uart++;
        contador_sensor++;
    }

    return 0;
}
