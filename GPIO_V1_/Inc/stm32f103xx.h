/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version    : 2.0       ******************/
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
	volatile u32	AHBSTR 		;
	volatile u32	CFGR2 		;

}Rcc_REGDef_t;

#define RCC_u32_BASE_ADDRESS		 0x40021000UL
#define RCC		((volatile Rcc_REGDef_t*)RCC_u32_BASE_ADDRESS)
/*************************************************************/

/************************GPIOx Registers 	**********************/
typedef struct
{
	volatile u32    CRL		;   	
	volatile u32	CRH		;
	volatile u32	IDR		;
	volatile u32	ODR		;
	volatile u32	BSRR	;
	volatile u32	BRR		;
	volatile u32	LCKR	;

}GPIOx_REGDef_t;
/**********************************  PORTA  **************************************/

#define GPIOA_u32_BASE_ADDRESS		  0x40010800UL
#define GPIOA		((volatile GPIOx_REGDef_t*)GPIOA_u32_BASE_ADDRESS)

/**********************************  PORTB  **************************************/
#define GPIOB_u32_BASE_ADDRESS		  0x40010C00UL
#define GPIOB		((volatile GPIOx_REGDef_t*)GPIOB_u32_BASE_ADDRESS)

/**********************************  PORTC  **************************************/
#define GPIOC_u32_BASE_ADDRESS		  0x40011000UL
#define GPIOC		((volatile GPIOx_REGDef_t*)GPIOC_u32_BASE_ADDRESS)
/*************************************************************/


#endif
