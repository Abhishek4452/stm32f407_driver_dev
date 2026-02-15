/*
 * STM32f407_I2C_driver.h
 *
 *  Created on: 01-Feb-2026
 *      Author: debian
 */

#ifndef STM32F407_I2C_H_
#define STM32F407_I2C_H_

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

// defining the configuration of @I2C_config_t

/* speed configure */
#define I2C_SCL_SPEED_SM     100000
#define I2C_SCL_SPEED_FM     400000 // we can configure according to our requirement
#define I2C_SCL_SPEED_FM2k   200000 // configure itself according to the requirement

/* ACK control */
#define I2C_ACK_ENABLE       1
#define I2C_ACK_DISABLE	     0 //default

/* duty cycle control */
#define I2C_FM_DUTY_2	   	 0 // from Reference manual
#define I2C_FM_duty_16_9	 1

/* STATUS FLAG - from the status register */
#define I2C_FLAG_TXE       		(1<< I2C_SR1_TxE)
#define I2C_FLAG_RXNE       	(1<<I2C_SR1_RxNE)
#define I2C_FLAG_SB         	(1<<I2C_SR1_SB)
#define I2C_FLAG_BTF         	(1<<I2C_SR1_BTF)
#define I2C_FLAG_ADDR         	(1<<I2C_SR1_ADDR)
#define I2C_FLAG_STOPF         	(1<<I2C_SR1_STOPF)
#define I2C_FLAG_BERR         	(1<<I2C_SR1_BERR)
#define I2C_FLAG_ARLO         	(1<<I2C_SR1_ARLO)
#define I2C_FLAG_AF         	(1<<I2C_SR1_AF)
#define I2C_FLAG_OVR         	(1<<I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT        (1<<I2C_SR1_TIMEOUT)


/*
 *                                               I 2 C   D R I V E R   F I L E
 */
/*
 *    PERIPHERAL CLK SETUP
 */
void I2C_periClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi); // Do it yourself

/*
 *  INIT and DE-Init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);

/*
 * IRQ configuration and ISR handling
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx); // DIY

/*
 *  MASTER SEND DATA
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,uint8_t Len,uint8_t SlaveAddr);

/*
 *  Data send and receive
 */
void I2C_SendData(I2C_RegDef_t *pI2Cx,uint8_t *pTxBuffer,uint32_t Len);
void I2C_ReceiveData(I2C_RegDef_t *pI2Cx,uint8_t *pRxBuffer,uint32_t Len);
/*
 *  IRQ configuration and ISR handling
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber,uint8_t ENorDI);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/*
 * other peripheral control APIs
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi); // DIY

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName); // may be not yet done


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv);

#endif /* STM32F407_I2C_H_ */
