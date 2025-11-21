/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 30/6/2025    ******************/
/********************Version    : 3.0       ******************/
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

/************************SYSTICK Registers 	**********************/
typedef struct
{
	volatile u32    CTRL	;   	
	volatile u32	LOAD	;
	volatile u32	VAL		;
	volatile u32	CALIB	;	
	
}SYSTICK_REGDef_t;

#define SYSTICK_u32_BASE_ADDRESS		 0xE000E010UL
#define SYSTICK		((volatile SYSTICK_REGDef_t*)SYSTICK_u32_BASE_ADDRESS)
/*************************************************************/




/************************  NVIC Registers 	**********************/
typedef struct
{
	volatile u32    ISER[32]	;   	//ISER 0-->2
	volatile u32    ICER[32]	; 		//ICER 0-->2
	volatile u32    ISPR[32]	;	    //ISPR 0-->2
	volatile u32    ICPR[32]	;		//ICPR 0-->2
	volatile u32    IABR[64]	;		//IABR 0-->2
	volatile u32    IPR [9]	    ;		//IPR  0-->20
	//volatile u32    STIR	    ;
}NVIC_REGDef_t;

#define SCB_AIRCR				(*(volatile u32*)(0xE000ED0C))
#define NVIC_u32_BASE_ADDRESS		 0xE000E100UL
#define NVIC		((volatile NVIC_REGDef_t*)NVIC_u32_BASE_ADDRESS)
/*************************************************************/








#endif
