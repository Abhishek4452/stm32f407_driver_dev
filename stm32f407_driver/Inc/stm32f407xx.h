/*
 * stm32f407xx.h
 * NOTE - please include the path of this file from the setting -> gcc compiler -> add path -> ok and apply changes
 *
 *  Created on: 04-Jan-2026
 *      Author: debian
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_


#include <stdint.h>
// HAL _, DRV_ these are the perfix which is used to easly identifing which layer code is it .
// while coding it is also possible that middleware also using the same micro name so to deal with such problem we use suffix

#define DRV_FLASH_BASEADDR        0x08000000U  // by default compiler will treat this as signed integer, but address can't be signed therfore either we type cast this or simply write U
#define DRV_SRAM_BASEADDR         0x20000000U
#define DRV_SRAM                  SRAM_BASEADDR
#define DRV_SRAM2_BASEADDR        0x2001C000U
#define DRV_ROM_BASEADDR          0x1FFF0000U  // ROM ALSO CALLED SYSTEM MEMORY

// ********************** BUS DOMAIN OF THE STM32f407 *************************************

#define DRV_PERI_ADDR             0x40000000U
#define DRV_APB1_PERI_ADDR        PERI_ADDR
#define DRV_APB2_PERI_ADDR        0x40010000U
#define DRV_AHB1_PERI_ADDR        0x40020000U
#define DRV_AHB2_PERI_ADDR        0x50000000U


// *********************** AHB1 BUS PERIPHERAL ******************************************* //


#define DRV_GPIOA_BASEADDR        (APB1_PERI_ADDR + 0000) // 0000 is our off set
#define DRV_GPIOB_BASEADDR        (APB1_PERI_ADDR + 0400)
#define DRV_GPIOC_BASEADDR        (APB1_PERI_ADDR + 0800)
#define DRV_GPIOD_BASEADDR        (APB1_PERI_ADDR + 0C00)
#define DRV_GPIOE_BASEADDR        (APB1_PERI_ADDR + 1000)
#define DRV_GPIOF_BASEADDR        (APB1_PERI_ADDR + 1400)
#define DRV_GPIOG_BASEADDR        (APB1_PERI_ADDR + 1800)
#define DRV_GPIOH_BASEADDR        (APB1_PERI_ADDR + 1C00)
#define DRV_GPIOI_BASEADDR        (APB1_PERI_ADDR + 2000)
// ------------------------------------- RCC ----------------------------------------------------
#define DRV_RCC_BASEADDR          (APB1_PERI_ADDR + 3800)



/* communication peripheral hanging on APB1 BUS
 *
 */

#define DRV_I2C1_BASEADDR            (PERI_ADDR+5400)
#define DRV_I2C2_BASEADDR            (PERI_ADDR+5800)
#define DRV_I2C3_BASEADDR            (PERI_ADDR+5C00)

#define DRV_SPI2_BASEADDR            (PERI_ADDR+3800)
#define DRV_SPI3_BASEADDR            (PERI_ADDR+3C00)

#define DRV_USART2_BASEADDR          (PERI_ADDR+4400)
#define DRV_USART3_BASEADDR          (PERI_ADDR+4800)
#define DRV_UART4_BASEADDR           (PERI_ADDR+4C00)
#define DRV_UART5_BASEADDR           (PERI_ADDR+5000)


/*
 * BUS HANGING ON APB2 BUS
 */

#define DRV_USART1_BASEADDR           (APB2_PERI_ADDR+1000)
#define DRV_USART6_BASEADDR			  (APB2_PERI_ADDR+1400)

#define DRV_SPI1_BASEADDR			  (APB2_PERI_ADDR+3000)

#define DRV_SYSCFG_BASEADDR			  (APB2_PERI_ADDR+3800)

#define DRV_EXTI_BASEADDR			  (APB2_PERI_ADDR+3C00)


/// ********************************************** PERIPHERAL REGISTER DECLEARATION ************************************************************
typedef struct
{
	volatile int32_t MODER;    //                    GPIO port mode register                               offset -- 0x00
	volatile int32_t OTYPER;   //                    GPIO port output type register                        offset -- T0x04
	volatile int32_t OSPEEDR;  //                    GPIO port output speed register                       offset -- D0x08
	volatile int32_t PUPDR;    //                    GPIO port pull-up/pull-down register                  offset -- R0x0C
	volatile int32_t IDR;      //                    GPIO port input data register                         offset -- 0x10
	volatile int32_t ODR;      //                    GPIO port output data register                        offset -- 0x14
	volatile int32_t BSRR;     //                    GPIO port bit set/reset register                      offset -- 0x18
	volatile int32_t LCKR;     //                    GPIO port configuration lock register                 offset -- 0x1C
	volatile int32_t AFRL;     //                    GPIO alternate function low register                  offset -- 0x20
	volatile int32_t AFRH;     //                    GPIO alternate function high register                 offset -- 0x24

}GPIO_RegDef_t;

//  --------------------------------------------- REGISTER DECLERATION FOR PERIPHERAL --------------------------------------------------------------------

typedef struct
{
	volatile int32_t RCC_CR;  		 //				RCC clock control register     								    offset = 0x00
	volatile int32_t RCC_PLLCFGR;    //				RCC PLL configuration register 									offset = 0x04
	volatile int32_t RCC_CFGR; 	     //				RCC clock configuration register     							offset =  0x08
	volatile int32_t RCC_CIR; 	     //				RCC clock interrupt register    							     offset = 0x0C
	volatile int32_t RCC_AHB1RSTR;   //				RCC AHB1 peripheral reset register								offset = 0x10
	volatile int32_t RCC_AHB2RSTR;   //			 	RCC AHB2 peripheral reset register  							offset = 0x14
	volatile int32_t RCC_AHB3RSTR;   //				RCC AHB3 peripheral reset register 							    offset = 0x18
	volatile int32_t RCC_APB1RSTR;   //				RCC APB1 peripheral reset register   							offset = 0x20
	volatile int32_t RCC_APB2RSTR;   //				RCC APB2 peripheral reset register 							    offset = 0x24
	volatile int32_t RCC_AHB1ENR;    //				RCC AHB1 peripheral clock enable register                       offset=  0x30
	volatile int32_t RCC_AHB2ENR;    //				RCC AHB2 peripheral clock enable register   				   	offset = 0x34
	volatile int32_t RCC_AHB3ENR;    //				RCC AHB3 peripheral clock enable register    					offset = 0x38
	volatile int32_t RCC_APB1ENR;    //				RCC APB1 peripheral clock enable register						offset = 0x40
	volatile int32_t RCC_APB2ENR;    //				RCC APB2 peripheral clock enable register 						offset = 0x44
	volatile int32_t RCC_AHB1LPENR;  //				RCC AHB1 peripheral clock enable in low power mode register 	offset = 0x50
	volatile int32_t RCC_AHB2LPENR;  //				RCC AHB2 peripheral clock enable in low power mode register     offset = 0x54
	volatile int32_t RCC_AHB3LPENR;  //				RCC AHB3 peripheral clock enable in low power mode register		offset = 0x58
	volatile int32_t RCC_APB1LPENR;  //				RCC APB1 peripheral clock enable in low power mode register	    offset = 0x60
	volatile int32_t RCC_APB2LPENR;  //				RCC APB2 peripheral clock enabled in low power mode  			offset = 0x64
	volatile int32_t RCC_BDCR;  	 //				RCC Backup domain control register  						    offset = 0x70
	volatile int32_t RCC_CSR;  		 //				RCC clock control & status register  						    offset = 0x74
	volatile int32_t RCC_SSCGR; 	 //				RCC spread spectrum clock generation register				    offset = 0x80
	volatile int32_t RCC_PLLI2SCFGR; //				RCC PLLI2S configuration register 							    offset = 0x84


}RCC_RegDef_t;






//// ********************************************* PERIPHERAL DEFINATION  ( type casted value )************************************************************

#define GPIOA                         ((GPIO_RegDef_t*) DRV_GPIOA_BASEADDR)
#define GPIOB                         ((GPIO_RegDef_t*) DRV_GPIOB_BASEADDR)
#define GPIOC                         ((GPIO_RegDef_t*) DRV_GPIOC_BASEADDR)
#define GPIOD                         ((GPIO_RegDef_t*) DRV_GPIOD_BASEADDR)
#define GPIOE                         ((GPIO_RegDef_t*) DRV_GPIOE_BASEADDR)
#define GPIOF                         ((GPIO_RegDef_t*) DRV_GPIOF_BASEADDR)
#define GPIOG                         ((GPIO_RegDef_t*) DRV_GPIOG_BASEADDR)
#define GPIOH                         ((GPIO_RegDef_t*) DRV_GPIOH_BASEADDR)
#define GPIOI                         ((GPIO_RegDef_t*) DRV_GPIOI_BASEADDR)

#define RCC                           ((RCC_RegDef_t*) DRV_RCC_BASEADDR)

// ************************************************ CLK ENABLE MACRO FOR GPIOx ***********************************************************
#define GPIOA_PCLK_EN()                 (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()					(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() 				(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()					(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()					(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()					(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()					(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()					(RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()					(RCC->AHB1ENR |= (1<<8))

// ************************************************ CLK ENABLE MACRO FOR I2Cx ***********************************************************
#define I2C1_PCLK_EN()					(RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() 					(RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()					(RCC->APB1ENR |= (1<<23))

// ************************************************ CLK ENABLE MACRO FOR SPIx ***********************************************************
#define SPI2_PCLK_EN()                  (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()                  (RCC->APB1ENR |= (1<<15))
#define SPI1_PCLK_EN()					(RCC->APB2ENR |=  (1<<12))
// ************************************************ CLK ENABLE MACRO FOR USARTx ***********************************************************
#define USART2_PCLK_EN()					(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()					(RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()						(RCC->APB1ENR |= (1<<19))
#define UART5_PCLK_EN()						(RCC->APB1ENR |= (1<<20))
#define USART1_PCLK_EN()					(RCC->APB2ENR |= (1<<4))
#define USART6_PCLK_EN()					(RCC->APB2ENR |= (1<<5))
// ************************************************ CLK ENABLE MACRO FOR SYSCFG ***********************************************************
#define SYSCFG_PCLK_EN() 					(RCC->APB2ENR |= (1<<14))


// ------------------------------------------------- CLK DISABLE FOR I2Cx peripheral -----------------------------------------------------------------
#define I2C1_PCLK_DI()					(RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() 					(RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()					(RCC->APB1ENR &= ~(1<<23))
// ------------------------------------------------- CLK DISABLE FOR GPIOx peripheral -----------------------------------------------------------------
#define GPIOA_PCLK_DI()                 (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() 				(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()					(RCC->AHB1ENR &= ~(1<<8))
// ------------------------------------------------- CLK DISABLE FOR SPIx peripheral -----------------------------------------------------------------
#define SPI2_PCLK_DI()                  (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()                  (RCC->APB1ENR &= ~(1<<15))
#define SPI1_PCLK_DI()					(RCC->APB2ENR &= ~(1<<12))
// ************************************************ CLK DISABLE MACRO FOR SYSCFG ***********************************************************
#define SYSCFG_PCLK_DI() 					(RCC->APB2ENR &= ~(1<<14))




#endif /* STM32F407XX_H_ */


















