/*
 * spi_driver.c
 *
 *  Created on: 13-Jan-2026
 *      Author: debian
 */
#include "stm32f407_spi_driver.h"

//************************************************ A P I  FOR USER  * ******************************************


/*
 *    PERIPHERAL CLK SETUP
 */
void SPI_periClockControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi){

	if(EnOrDi == ENABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3 ){
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_EN();
		}

	}
	else{
		// disabling the spi
		if(pSPIx == SPI1){
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3 ){
			SPI3_PCLK_DI();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_DI();
		}
}
}







/*
 *  INIT and DE-Init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);

/*
 * IRQ configuration and ISR handling
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 *  Data send and receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len);
/*
 *  IRQ configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t ENorDI);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
/*
 * other peripheral control APIs
 */




