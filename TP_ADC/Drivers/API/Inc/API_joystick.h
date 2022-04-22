/*
 * API_joystick.h
 *
 *  Created on: 9 abr. 2022
 *      Author: javelasco
 */

#include "main.h"
#include <stdbool.h>
#include <stdio.h>

#ifndef API_INC_API_JOYSTICK_H_
#define API_INC_API_JOYSTICK_H_

#define	axisLowerLimit	400
#define axisUpperLimit	600

typedef enum {
	IDDLE_AXIS,
	UP_AXIS,
	DOWN_AXIS,
	RIGHT_AXIS,
	LEFT_AXIS,
	B_PRESSED
} AxisState;
AxisState		axisState;

/**
  * @brief JOYSTICK Initialization Function
  * @param pushButtonPort
  * @retval pushButtonPin
  */
void	myJoystick_init(GPIO_TypeDef* pushButtonPort, uint8_t pushButtonPin);

uint8_t	myJoystick_status(void);

bool	myJoystick_pushButtonAxis(void);


#endif /* API_INC_API_JOYSTICK_H_ */
