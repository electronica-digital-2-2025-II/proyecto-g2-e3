[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/eiNgq3fR)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=22047215&assignment_repo_type=AssignmentRepo)
# Sistema automatizado de alimentacion para mascotas
<!-- Cambiar el titulo "Proyecto" por el nombre del proyecto -->

# Integrantes
- Santiago A. Campos Mora
- Juan Pablo Prieto Vergara
- Santiago Herrera Acuña
<!-- Califico el informe unicamente a los integrantes que esten referenciados aqui y en el informe (PDF) -->

Indice:

1. [Descripción](#descripción)
2. [Informe](#informe)
3. [Implementación](#implementacion)
4. [Lista de anexos](#anexos)

## Descripción

El proyecto consiste en una estructura impresa en 3D que sirve como dispensador de comida para mascotas, enfocado mas en gatos. Este comedero realizado en PLA tiene incorporado un servo motor, el cual permite abirir una escotilla para que la comida caiga por gravedad y llene un recipiente de donde la mascota podra alimentarse. Este proyecto esta enfocado en automatizar el proceso, por lo cual tiene dos perifericos importantes para ello: el modulo HC-06 y el sensor RCWL-0516. El primero de estos componentes permite la comunicaion con el comedero via Bluetooth, la orden de activacion para el motor se envia desde una aplicacion en Android de nuestra autoria. Este modulo funciona por comunicacion UART para enviar o recibir informacion de la FPGA. Finalmente, el sensor RCWL es un sensor de movimiento de efecto dopler, el cual enviar ondas RF a todas las direcciones en un rango de 5 a 7 metros, por lo cual, al detectar movimiento envia una señal para que el servo motor se active. 

<!-- Descripción general y lo mas completa posible del proyecto" -->

## Informe
El informe en formato IEEE debidamente documentado se encuentra en este repositorio, pudiendo acceder a el desde el siguiente link:
[Informe final del  proyecto](/scr/entrega_final)
<!-- Link que permita acceder al Informe, el cual debe estar subido a este repositorio -->

## Implementación

<!-- Video explicativo del funcionamiento del proytecto -->
A continuacion el codigo en C para el funcionamiento del video:

NO OLVIDAR AGREGAR EL ARCHIVO .C Y .H EN LA CARPETA SCR Y REFERENCIARLA EN EL LINK

[main.c](/scr/)

Para la ID o direcciones de memoria, se tiene el siguiente archivo .h:

[xparameters.h](/scr/)

Finalmente el block desing creado en vivado

[Block desing](/scr/block_desing)


<!-- CREAR UN DIRECTORIO CON EL NOMBRE "src" DONDE INVLUYAN LAS FUENTE (.c Y .h) QUE CREARON PARA EL PROOYECTO-->

<!-- NO OLVIDAD SUBIR EL PDF GENERADOR EN DEL BLOCK DESIGN-->
