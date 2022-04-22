/*
 * API_joystick.c
 *
 *  Created on: 9 abr. 2022
 *      Author: javelasco
 */


#include "../Inc/API_joystick.h"
#include "../Inc/API_delay.h"

static bool	myJoystick_rightAxis(void);
static bool	myJoystick_leftAxis(void);
static bool	myJoystick_upAxis(void);
static bool	myJoystick_downAxis(void);
static bool myJostick_pushButtonAxis(void);


#define _delay 40

// Create a structs array of type delay_t
static delay_t debounceDelay;

typedef enum {
	FREE,
	FALLING,
	RAISING,
	PRESSED,
} DebounceState;
DebounceState	buttonState;

typedef struct {
	GPIO_TypeDef*	_pushButtonPort;
	uint8_t			_pushButtonPin;

	uint16_t		_xAxisValue;
	uint16_t		_yAxisValue;
	bool			_pushButtonValue;
} MyJoystick;
MyJoystick	myJoystick;

#define	x_axis	0
#define	y_axis	1

#define	adc_number	2
uint32_t adc_value[adc_number];

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* Private function prototypes -----------------------------------------------*/
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);

void myJoystick_init(GPIO_TypeDef* pushButtonPort, uint8_t pushButtonPin){
	myJoystick._pushButtonPort 	= pushButtonPort;
	myJoystick._pushButtonPin 	= pushButtonPin;
	myJoystick._pushButtonValue = true;

	MX_DMA_Init();
	MX_ADC1_Init();

	buttonState = FREE;
	axisState 	= IDDLE_AXIS;

	HAL_ADC_Start_DMA(&hadc1, adc_value, adc_number);
}

uint8_t	myJoystick_status(void){
	if(myJoystick_rightAxis()){
		axisState 	= RIGHT_AXIS;
		return		axisState;
	}
	else if(myJoystick_leftAxis()){
		axisState 	= LEFT_AXIS;
		return		axisState;
	}
	else if(myJoystick_upAxis()){
		axisState 	= UP_AXIS;
		return		axisState;
	}
	else if(myJoystick_downAxis()){
		axisState 	= DOWN_AXIS;
		return		axisState;
	}
	else if(!myJostick_pushButtonAxis()){
		axisState 	= B_PRESSED;
		return		axisState;
	}
	else {
		axisState 	= IDDLE_AXIS;
		return		axisState;
	}
}

bool myJoystick_rightAxis(void){
	myJoystick._xAxisValue = adc_value[x_axis];

	// Gets a move to the right, if the ADC value is greater than and equal to the axis upper limit (600) and less than 1023.
	if(myJoystick._xAxisValue >= axisUpperLimit && myJoystick._xAxisValue <= 1023){
		return true;
	}
	else{
		return false;
	}
}

bool myJoystick_leftAxis(void){
	myJoystick._xAxisValue = adc_value[x_axis];

	// Gets a move to the left, if the ADC value is greater than and equal to 0 and less than the lower limit of the axis (400).
	if(myJoystick._xAxisValue >= 0 && myJoystick._xAxisValue < axisLowerLimit){
		return true;
	}
	else{
		return false;
	}
}

bool myJoystick_upAxis(void){
	myJoystick._yAxisValue = adc_value[y_axis];

	// Gets a move to the up, if the ADC value is greater than and equal to 0 and less than the lower limit of the axis (400).
	if(myJoystick._yAxisValue >= 0 && myJoystick._yAxisValue < axisLowerLimit){
		return true;
	}
	else{
		return false;
	}
}

bool myJoystick_downAxis(void){
	myJoystick._yAxisValue = adc_value[y_axis];

	// Gets a move to the down, if the ADC value is greater than and equal to the axis upper limit (600) and less than 1023.
	if(myJoystick._yAxisValue >= axisUpperLimit && myJoystick._yAxisValue <= 1023){
		return true;
	}
	else{
		return false;
	}
}

bool myJostick_pushButtonAxis(void){
	switch(buttonState){
		case FREE:
			// If the button has been pressed, it starts the button's state machine.
			if(!HAL_GPIO_ReadPin(myJoystick._pushButtonPort, myJoystick._pushButtonPin)){
				buttonState = FALLING;
				// Initializes the structure with a delay of 40 ms.
				delayInit(&debounceDelay, _delay);
			}
			myJoystick._pushButtonValue = true;
			break;
		case FALLING:
			// If the button is still in low state after the delay. Continue with the next state (Pressed) of the state machine.
			if(delayRead(&debounceDelay)){
				if(!HAL_GPIO_ReadPin(myJoystick._pushButtonPort, myJoystick._pushButtonPin)){
					buttonState = PRESSED;
					myJoystick._pushButtonValue = false;
					break;
				}
				myJoystick._pushButtonValue = true;
			}
			else {
				buttonState = FREE;
				myJoystick._pushButtonValue = true;
			}
			break;
		case PRESSED:
			// If the button has been released. Continue with the next state (Raising) of the state machine.
			if(HAL_GPIO_ReadPin(myJoystick._pushButtonPort, myJoystick._pushButtonPin)){
				buttonState = RAISING;
				// Initializes the structure with a delay of 40 ms.
				delayInit(&debounceDelay, _delay);
				myJoystick._pushButtonValue = true;
			}
			break;
		case RAISING:
			// If the button is still high after the delay. Return to the initial state (Free) of the state machine.
			if(delayRead(&debounceDelay)){
				if(HAL_GPIO_ReadPin(myJoystick._pushButtonPort, myJoystick._pushButtonPin)){
					buttonState = FREE;
					myJoystick._pushButtonValue = true;
					break;
				}
				else {
					buttonState = PRESSED;
					myJoystick._pushButtonValue = false;
				}
			}
			break;
		default:
			myJoystick._pushButtonValue = true;
	}
	return myJoystick._pushButtonValue;
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_10B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }


  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}


