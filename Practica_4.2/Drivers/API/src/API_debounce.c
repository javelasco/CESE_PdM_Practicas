
#include "main.h"
#include "../Drivers/API/inc/API_debounce.h"
#include "../Drivers/API/inc/API_delay.h"

#define _delay 40

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;

debounceState_t state;

static Led_TypeDef myLED;

// Create a structs array of type delay_t
static delay_t debounceDelay;

void debounceFSM_init(Led_TypeDef Led){

	myLED = Led;

	// Initialize the three leds.
	BSP_LED_Init(myLED);
	// Power off the three leds.
	BSP_LED_Off(myLED);

	// Initialize the three structs.
	delayInit(&debounceDelay, _delay);	//delay 40ms

	state = BUTTON_UP;
}

void buttonPressed(){
	myDelay = 500;
}

void buttonReleased(){
	myDelay = 100;
}

void debounceFSM_update(bool buttonState){
	if(buttonState){							// Was the button pushed?
		switch(state){
			case BUTTON_UP:
				if(delayRead(&debounceDelay)){
					state = BUTTON_FALLING;
				}
				break;

			case BUTTON_FALLING:
				if(delayRead(&debounceDelay)){
					state = BUTTON_DOWN;
					buttonPressed();
				}
				break;

			case BUTTON_DOWN:
				if(delayRead(&debounceDelay)){}
				break;

			case BUTTON_RAISING:
				if(delayRead(&debounceDelay)){}
				break;

			default:
				if(delayRead(&debounceDelay)){
					state = BUTTON_UP;
					myDelay = 500;
					BSP_LED_Off(myLED);
				}
		}
	}
	else if(!buttonState){ 							// Was the button released?
		switch(state){
			case BUTTON_UP:
				if(delayRead(&debounceDelay)){}
				break;

			case BUTTON_FALLING:
				if(delayRead(&debounceDelay)){}
				break;

			case BUTTON_DOWN:
				if(delayRead(&debounceDelay)){
					state = BUTTON_RAISING;
				}
				break;

			case BUTTON_RAISING:
				if(delayRead(&debounceDelay)){
					state = BUTTON_UP;
					buttonReleased();
				}
				break;

			default:
				if(delayRead(&debounceDelay)){
					state = BUTTON_UP;
					myDelay = 100;
					BSP_LED_Off(myLED);
				}
		}
	}
}


