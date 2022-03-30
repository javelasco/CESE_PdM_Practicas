#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

#include <stdbool.h>
#include <stdio.h>

extern uint32_t myDelay;						// Variable externa compartida del main.c

void debounceFSM_init(Led_TypeDef Led);			// Recibe el Led a oscilar e inicializa la función antirebote del FSM
void debounceFSM_update(bool buttonState);		// Recibe el valor boleano del pulsador, analiza y resuelve la logica de transición de estados
void buttonPressed(void);						// Togglear LED a 500ms
void buttonReleased(void);						// Togglear LED a 100ms

#endif
