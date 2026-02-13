/*
 *                                    STM32f407_I2C_driver.c
 *
 *  Created on: 01-Feb-2026
 *      Author: debian
 */


/*
 *                                               I 2 C   D R I V E R   F I L E
 */



/*
 *    PERIPHERAL CLK SETUP
 */
void I2C_periClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi){
	if (EnOrDi== ENABLE){
		if(*pI2Cx == I2C1){
			I2C1_PCLK_EN();
		}
		else if (*pI2Cx == I2C2){
			I2C2_PCLK_EN();
		}
		else if(*pI2Cx == I2C3){
			I2C3_PCLK_EN();
		}
	}
	else{
		if(*pI2Cx == I2C1){
			I2C1_PCLK_DI();
		}
		else if (*pI2Cx == I2C2){
			I2C1_PCLK_DI();
		}
		else if(*pI2Cx == I2C3){
			I2C1_PCLK_DI();
		}
	}
}

/*
 *  INIT and DE-Init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);

/*
 * IRQ configuration and ISR handling
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx){
	if(*pI2Cx == I2C1){
		I2C1_REG_RESET();
	}
	else if (*pI2Cx == I2C2){
		I2C2_REG_RESET();
	}
	else if(*pI2Cx == I2C3){
		I2C3_REG_RESET();
	}
}

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
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName);


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv);


