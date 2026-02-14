/*
 *                                    STM32f407_I2C_driver.c
 *
 *  Created on: 01-Feb-2026
 *      Author: debian
 */


/*
 *                                               I 2 C   D R I V E R   F I L E
 */
#include "STM32f407_I2C_driver.h"



/*
 *    PERIPHERAL CLK SETUP
 */
void I2C_periClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi){
	if (EnOrDi== ENABLE){
		if(pI2Cx == I2C1){
			I2C1_PCLK_EN();
		}
		else if (pI2Cx == I2C2){
			I2C2_PCLK_EN();
		}
		else if(pI2Cx == I2C3){
			I2C3_PCLK_EN();
		}
	}
	else{
		if(pI2Cx == I2C1){
			I2C1_PCLK_DI();
		}
		else if (pI2Cx == I2C2){
			I2C1_PCLK_DI();
		}
		else if(pI2Cx == I2C3){
			I2C1_PCLK_DI();
		}
	}
}
// ======================================== I 2 C function BEGIN ==========================================
uint32_t RCC_GetPLLOutputClock(void){
	// do later
	return 0;
}
uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};
uint32_t RCC_GetPCLKValue(void){
	uint32_t pclk1,SystemClk,temp;
	uint8_t clksrc,ahbp,ahb1p;

	clksrc = ((RCC->CFGR>>2)&0x3); // bit masking

	if (clksrc == 0){
		// 00 HSI oscillator used as clk src
		SystemClk = 16000000;
	}
	else if (clksrc == 1){
		// 01 HSE oscillator used as clk src
		SystemClk = 8000000;
	}
	else if (clksrc == 2){
		// 10 PLL decide the clk src
		SystemClk = RCC_GetPLLOutputClock();
	}

	// PRESCALAR VALUE OF AHB , which comes from the RCC(system bus)
	temp = ((RCC->CFGR >> 4)& 0xF);

	if (temp < 8){  // for AHB bus
		ahbp =1;
	}
	else{ // this If - else gives us the division factor
		ahbp = AHB_PreScaler[temp-8];
	}


	// APB1 prescalar
	temp = ((RCC->CFGR >> 10)& 0x7);
	if (temp < 8){
		ahb1p =1;
	}
	else{ // this If - else gives us the division factor
		ahb1p = APB1_PreScaler[temp-4];
	}

	pclk1 = (SystemClk/ahbp/ahb1p);

	return pclk1;
}
// ======================================== I 2 C function END ==========================================

/*
 *  INIT and DE-Init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle){
	uint32_t tempreg = 0;
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl <<10;

}

/*
 * IRQ configuration and ISR handling
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx){
	if(pI2Cx == I2C1){
		I2C1_REG_RESET();
	}
	else if (pI2Cx == I2C2){
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


