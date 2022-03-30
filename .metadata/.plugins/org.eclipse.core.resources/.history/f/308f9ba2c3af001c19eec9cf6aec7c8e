#ifndef __API_DELAY_H
#define __API_DELAY_H

#include <stdbool.h>
#include <stdio.h>

typedef uint32_t 	tick_t;
typedef bool 		bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

//This function starts the structure. It receives as parameter the name of the structure and the initial delay.
void 	delayInit(delay_t * delay, tick_t duration);

/*This function constantly validates if the indicated delay has elapsed.
It receives the name of the structure as its only parameter.*/
bool_t 	delayRead(delay_t * delay);

//Receives the name of the structure and the new delay as parameters.
void 	delayWrite(delay_t * delay, tick_t duration);

#endif
