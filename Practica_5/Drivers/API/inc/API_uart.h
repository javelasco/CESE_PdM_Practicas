#ifndef __API_UART_H
#define __API_UART_H

#include <stdbool.h>
#include <stdio.h>

typedef bool	bool_t;

UART_HandleTypeDef UartHandle;

// Función que inicializa el UART
bool_t uartInit();

// Función que envía un string sin salto de linea
void uartSendString(uint8_t * pstring);

// Función que envía un string con salto de linea
void uartSendStringln(uint8_t * pstring);

// Función que envía un string y la cantidad de bytes a imprimir sin salto de linea
void uartSendStringSize(uint8_t * pstring, uint16_t size);

// Función que envía un string y la cantidad de bytes a imprimir con salto de linea
void uartSendStringlnSize(uint8_t * pstring, uint16_t size);

// Función que recibe un byte de la computadora y lo almacena en buffer
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif
