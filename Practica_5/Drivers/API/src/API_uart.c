
#include "main.h"
#include "../Drivers/API/inc/API_uart.h"

static uint8_t mySize;

// Función que inicializa el UART
bool_t uartinit(){

	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */

	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if (HAL_UART_Init(&UartHandle) != HAL_OK){
	    /* Initialization Error */
	    //Error_Handler();
	    return false;
	  } else {
		  /* Output a message on Hyperterminal using printf function */
		  printf("\n\r UART has been started successfully.\n\r");
		  return true;
	  }
}

// Función que envía un string sin salto de linea
void uartSendString(uint8_t * pstring){
	mySize = strlen(pstring);

	HAL_UART_Transmit(&UartHandle, pstring, mySize, HAL_MAX_DELAY);
}

// Función que envía un string con salto de linea
void uartSendStringln(uint8_t * pstring){
	mySize = strlen(pstring);

	HAL_UART_Transmit(&UartHandle, pstring, mySize, HAL_MAX_DELAY);
	HAL_UART_Transmit(&UartHandle, "\n\r", 2, HAL_MAX_DELAY);
}

// Función que envía un string y la cantidad de bytes a imprimir sin salto de linea
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	mySize = strlen(pstring);

	if(size > mySize){
		size = mySize;
	}

	HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
}

// Función que envía un string y la cantidad de bytes a imprimir con salto de linea
void uartSendStringlnSize(uint8_t * pstring, uint16_t size){
	mySize = strlen(pstring);

	if(size > mySize){
		size = mySize;
	}

	HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
	HAL_UART_Transmit(&UartHandle, "\n\r", 2, HAL_MAX_DELAY);
}


// Función que recibe un byte de la computadora y lo almacena en buffer
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){
	if(!HAL_UART_Receive(&UartHandle, pstring, size, 10)){
		HAL_UART_Transmit(&UartHandle, pstring, size, 10);
	}
}

