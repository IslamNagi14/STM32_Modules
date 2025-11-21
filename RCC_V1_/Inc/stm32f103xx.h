/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : stm32f103xx   ******************/
/*************************************************************/

#ifndef  __STM32F103XX__H__
#define __STM32F103XX__H__


/************************RCC Registers 	**********************/
typedef struct
{
	volatile u32    CR      	;   	
	volatile u32	CFGR		;
	volatile u32	CIR  		;
	volatile u32	APB2RSTR	;
	volatile u32	APB1RSTR 	;
	volatile u32	AHBENR  	;
	volatile u32	APB2ENR		;
	volatile u32	APB1ENR		;
	volatile u32	BDCR		;
	volatile u32	CSR  		;
	

}Rcc_REGDef_t;

#define RCC_u32_BASE_ADDRESS		 0x40021000
#define RCC		((volatile Rcc_REGDef_t*)RCC_u32_BASE_ADDRESS)
/*************************************************************/


#endif
