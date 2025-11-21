/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : RCC          ******************/
/*************************************************************/

#ifndef  __RCC_INT_H__
#define __RCC_INT_H__

#include "StdTypes.h"
#include "errorStatuse.h"


void RCC_VidInitSysClk						(void);

ES_t RCC_enuStatePeripheralClk				(u8 Copy_u8Peripheral,u8 Copy_u8State);

ES_t RCC_enuStateMCOpin						(u8 Copy_u8SelectedClock);

ES_t RCC_enuStateCLKSecuritySys				(u8 Copy_u8State);

ES_t RCC_enuTrimHSI							(u32 Copy_u32TrimValKHz);/*in your trimming value in KHz, And try to make it retalive to (x*(40)Hz or x*(-40)Hz)
														               to get accurate trimming where x = 1,2,3,4,5,6,7,8. 	 	  */
ES_t RCC_enuStateClkSourceInterrupt			(u8 Copy_u8CLKsource,u8 Copy_u8State);

ES_t RCC_enuResetPeripheral				(u8 Copy_u8Peripheral);//This function for peripherals on APB1 and APB2 only(not used for AHB)
/**********************************STATES*******************************************/

#define RCC_u8_ENABLE		1
#define RCC_u8_DISABLE		0

/***********************************************************************************/


/********************************* MCO selections ****************************/

#define RCC_u8NO_CLOCK						0x0
#define RCC_u8SYS_CLOCK						0x4
#define RCC_u8HSI							0x5
#define RCC_u8HSE							0x6
#define RCC_u8PLL    						0x7


/*************************************************************************************/


/********************************* Clk source selections ****************************/

#define  RCC_u8HIGH_SPEED_EXTERNAL_CLOCK		0x1
#define  RCC_u8HIGH_SPEED_INTERNAL_CLOCK		0x0
#define  RCC_u8PHASE_LOCKED_LOOP_CLOCK          0x2

/*************************************************************************************/



/********************************* HSE configuration systems ****************************/

#define RCC_u8_CERAMIC_CRYSTAL                 5		//there is no bypass  and max freq input 25MHz
#define RCC_u8_RC							   63		//bypassed and freq 4-->16 MHz


/*************************************************************************************/

/*************************AHB Peripheral Clock enable register**********************/


#define  DMA1			0
#define  DMA2			1
#define  SRAM			2
#define  FLITF			4
#define  CRC			6
#define  FSMC			8
#define  SDIO			10

/************************************************************************************/

/*************************APB2 Peripheral Clock enable register**********************/


#define	 AFIO  			(32+0)
#define  IOPA			(32+2)
#define  IOPB			(32+3)
#define  IOPC			(32+4)
#define  IOPD			(32+5)
#define  IOPE			(32+6)
#define  IOPF			(32+7)
#define  IOPG			(32+8)
#define  ADC1			(32+9)
#define  ADC2			(32+10)
#define  TIM1			(32+11)
#define  SPI1			(32+12)
#define  TIM8			(32+13)
#define  USART1			(32+14)
#define  ADC3			(32+15)
#define  TIM9			(32+19)
#define  TIM10			(32+20)
#define  TIM11			(32+21)


/***********************************************************************************/


/*************************APB1 Peripheral Clock enable register**********************/


#define	 TIM2			(64+0)
#define  TIM3			(64+1)
#define  TIM4			(64+2)
#define  TIM5			(64+3)
#define  TIM6			(64+4)
#define  TIM7			(64+5)
#define  TIM12			(64+6)
#define  TIM13			(64+7)
#define  TIM14			(64+8)
#define  WWDG			(64+11)
#define  SPI2			(64+14)
#define  SPI3			(64+15)	
#define  USART2			(64+17)
#define  USART3			(64+18)
#define  USART4			(64+19)
#define  USART5			(64+20)
#define  I2C1			(64+21)
#define  I2C2			(64+22)
#define  USB			(64+23)
#define  CAN			(64+25)
#define  BKP			(64+27)
#define  PWR			(64+28)
#define  DAC			(64+29)


/***********************************************************************************/


#endif
