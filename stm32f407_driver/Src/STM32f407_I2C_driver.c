/*
 *                                    STM32f407_I2C_driver.c
 *
 *  Created on: 01-Feb-2026
 *      Author: debian
 */


/*
 *                                               I 2 C   D R I V E R   F I L E
 */
#include "stm32f407_I2C.h"

// ======================================= FUNCTION =================================
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
// ========================================================================

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
// ======================================== RCC  ==========================================
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
// ======================================== RCC ==========================================

/*
 *  INIT and DE-Init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle){
	uint32_t tempreg = 0;

	// ack control bit
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl <<10;
	pI2CHandle->pI2Cx->CR1 = tempreg;

	// configure the FREQ field of CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLKValue()/1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F); // 6 bits are valid

	// slave address -> oAR1 reg (own addr register)
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	// if you are using the 10 bit slave addr then add mode reg need to be set
	tempreg |= (1<<14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	// configure the clock  register
	uint16_t ccr_value = 0;
	if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM) // configure the ccr register
	{	// F/S value 0 by default & duty = 0 by default so no need to reset
		/*
		 *  calculation of the CCR value
		 *  Tscl = 2 CCR * Tpclk
		 *  ccr = Fpclk /(2*Fscl)
		 */
		// mode is standard
		ccr_value  = (RCC_GetPCLK1Value()/(2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= (ccr_value & 0xFFF); // masking the first 12 bit
	}
	else {
		// mode is fast
		tempreg |= (1<<15); // f/s mode is set
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle <<14);
		/* if duty = 0
		 * Tclk = 3* CCR*Tpclk
		 * ccr = (Fclk/(3*Fscl))
		 * else:
		 * Tclk = 25*CCR*Tpclk
		 * ccr = Fpclk / (25* Fscl)
		 */
		if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
			ccr_value = (RCC_GetPCLKValue() / (3* pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		else
		{
			ccr_value = (RCC_GetPCLKValue() / (25* pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		tempreg |= (ccr_value & 0xCFFF); // may be it will not work then set the 0xcfff = 0xfff
	}
	pI2CHandle->pI2Cx->CCR = tempreg;


	// TRISE register


}

/*
 * IRQ configuration and ISR handling
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx){
	if(pI2Cx == I2C1){
		I2C1_REG_RESET();
	}
	else if(pI2Cx == I2C2){
		I2C2_REG_RESET();
	}
	else if(pI2Cx == I2C3){
		I2C3_REG_RESET();
	}
}

/*
 *  SENDING DATA to SLAVE
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,uint8_t Len,uint8_t SlaveAddr){
	//1. generate The Start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
	//2. confirm the start genration is complete by checking the Sb flag in SR1
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_Flag_SB));
	//3. send the addr of the slave with r/w bit set to w(0)  (total 8 bit)
	//4. confirm that address phase is complete by checking the addr flag
	//5. clear the addr flag accoriding to its software sequence
	//6. send the data until len become 0
	/*  when len becomes zero wait for txe = 1 and btf =1 before generating the stop condition
	 *  note txe = 1, btf =1 , means that both sr and dr empty and next transmission should begin
	 *  when BTf scl will be stretched
	 */
	// 8. generate stop condition and mstr need not to wait doe the completion of stop condition
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1<<I2C_CR1_START);
}
// ========================================================================================================

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


