/*
 * STM32f407_I2C_driver.h
 *
 *  Created on: 01-Feb-2026
 *      Author: debian
 */

#ifndef STM32F407_I2C_DRIVER_H_
#define STM32F407_I2C_DRIVER_H_

#include "stm32f407xx.h"

//************************* CONFIGRATION STRUCTURE FOR I2C PERIPHERAL
typedef struct {
	uint32_t I2C_SCLSpeed;
	uint8_t I2C_DeviceAddress; // mention by the user
	uint8_t I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
}I2C_Config_t;

//************************* HANDLE STRUCTURE FOR I2C PERIPHERAL
typedef struct{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
}I2C_Handle_t;

// defining the configuration
#define I2C_SCL_SPEED_SM  100000
#define I2C_SCL_SPEED_FM  400000 // we can configure according to our requirement
#define I2C_ACK_ENABLE    1
#define I2C_ACK_DISABLE	  0 //default
#define I2C_FM_DUTY_2		0
#define I2C_FM_duty_16_9	1

#endif /* STM32F407_I2C_DRIVER_H_ */
