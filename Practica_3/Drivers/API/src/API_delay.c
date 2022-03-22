
#include "../Drivers/API/inc/API_delay.h"

//This function starts the structure. It receives as parameter the name of the structure and the initial delay.
void delayInit(delay_t * delay, tick_t duration ){
	if(duration <= 0 || duration == NULL)
		duration = 0;

	delay->duration = (tick_t)duration;
}

/*This function constantly validates if the indicated delay has elapsed.
It receives the name of the structure as its only parameter.*/
bool_t delayRead(delay_t * delay){
	if(delay->running){
		if(HAL_GetTick() >= (delay->startTime + delay->duration)){
			delay->running = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	}
}

//Receives the name of the structure and the new delay as parameters.
void delayWrite(delay_t * delay, tick_t duration){
	if(duration <= 0 || duration == NULL)
		duration = 0;

	delay->duration = (tick_t)duration;
}


