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
	volatile u32    IPR [9]	    ;		//IPR  0-->8
	//volatile u32    STIR	    ;
}NVIC_REGDef_t;

#define SCB_AIRCR				(*(volatile u32*)(0xE000ED0C))
#define NVIC_u32_BASE_ADDRESS		 0xE000E100UL
#define NVIC		((volatile NVIC_REGDef_t*)NVIC_u32_BASE_ADDRESS)
/*************************************************************/






/************************  EXTI Registers 	**********************/
typedef struct
{
	volatile u32    IMR	    ;   	
	volatile u32	EMR	    ;
	volatile u32	RTSR	;
	volatile u32	FTSR	;	
	volatile u32	SWIER	;	
	volatile u32	PR	    ;	
		
	
}EXTI_REGDef_t;

#define EXTI_u32_BASE_ADDRESS		 0x40010400UL
#define EXTI		((volatile EXTI_REGDef_t*)EXTI_u32_BASE_ADDRESS)
/*****************************************************************/

/************************  DMA Registers 	**********************/
typedef struct
{
	volatile u32    ISR    		  ;   	
	volatile u32	IFCR		  ;

	volatile u32	CCR1	      ;
	volatile u32	CNDTR1	      ;	
	volatile u32	CPAR1	      ;	
	volatile u32	CMAR1	      ;	
    volatile u32	reserved1	  ;

	volatile u32	CCR2	      ;
	volatile u32	CNDTR2	      ;	
	volatile u32	CPAR2	      ;	
	volatile u32	CMAR2	      ;
	volatile u32	reserved2	  ;
	
	
	volatile u32	CCR3	      ;
	volatile u32	CNDTR3	      ;	
	volatile u32	CPAR3	      ;	
	volatile u32	CMAR3	      ;
	volatile u32	reserved3	  ;

	volatile u32	CCR4	      ;
	volatile u32	CNDTR4	      ;	
	volatile u32	CPAR4	      ;	
	volatile u32	CMAR4	      ;
	volatile u32	reserved4	  ;
	
	volatile u32	CCR5    	  ;
	volatile u32	CNDTR5	      ;	
	volatile u32	CPAR5	      ;	
	volatile u32	CMAR5	      ;
	volatile u32	reserved5	  ;
	
	
	volatile u32	CCR6    	  ;
	volatile u32	CNDTR6	      ;	
	volatile u32	CPAR6	      ;	
	volatile u32	CMAR6	      ;	
	volatile u32	reserved6	  ;
	
	volatile u32	CCR7    	  ;
	volatile u32	CNDTR7	      ;	
	volatile u32	CPAR7	      ;	
	volatile u32	CMAR7	      ;	
	volatile u32	reserved7	  ;
		
	
}DMA_REGDef_t;

#define DMA_u32_BASE_ADDRESS		 0x40020000UL
#define DMA		((volatile DMA_REGDef_t*)DMA_u32_BASE_ADDRESS)
/*****************************************************************/



/************************  USART1 Registers 	**********************/
typedef struct
{
	volatile u32    SR      ;
	volatile u32	DR	    ;
	volatile u32    BRR 	;
	volatile u32	CR1	    ;
	volatile u32	CR2	    ;
	volatile u32	CR3	    ;
	volatile u32	GTPR	;



}USART1_REGDef_t;

#define USART1_u32_BASE_ADDRESS		 0x40013800UL
#define USART1		((volatile USART1_REGDef_t*)USART1_u32_BASE_ADDRESS)
/*****************************************************************/



/************************  ADC1 Registers 	**********************/
typedef struct
{
	volatile u32     SR       ;
	volatile u32	 CR1      ;
	volatile u32	 CR2      ;
	volatile u32     SMPR1 	  ;
	volatile u32     SMPR2 	  ;
	volatile u32	 JOFR1    ;
	volatile u32	 JOFR2    ;
	volatile u32	 JOFR3    ;
	volatile u32	 JOFR4    ;
	volatile u32	 HTR      ;
	volatile u32	 LTR      ;
	volatile u32	 SQR1	  ;
	volatile u32	 SQR2	  ;
	volatile u32	 SQR3	  ;
	volatile u32	 JSQR	  ;
	volatile u32	 JDR1	  ;
	volatile u32	 JDR2	  ;
	volatile u32	 JDR3	  ;
	volatile u32	 JDR4	  ;
	volatile u32	 DR	      ;


}ADC1_REGDef_t;

#define ADC1_u32_BASE_ADDRESS		 0x40012400UL
#define ADC1		((volatile ADC1_REGDef_t*)ADC1_u32_BASE_ADDRESS)
/*****************************************************************/



/************************  TIM(1/8) Registers 	**********************/
typedef struct
{
	volatile u32     CR1      ;
	volatile u32     CR2      ;
	volatile u32	 SMCR     ;
	volatile u32	 DIER     ;
	volatile u32     SR	      ;
	volatile u32     EGR 	  ;
	volatile u32	 CCMR1    ;
	volatile u32	 CCMR2    ;
	volatile u32	 CCER     ;

	volatile u16	 CNT      ;
	volatile u16	       :16;
	volatile u16	 PSC      ;
	volatile u16	       :16;
	volatile u16	 ARR      ;
	volatile u16	       :16;
	volatile u16	 RCR      ;
	volatile u16	       :16;
	volatile u16	 CCR1	  ;
	volatile u16	       :16;
	volatile u16	 CCR2	  ;
	volatile u16	       :16;
	volatile u16	 CCR3	  ;
	volatile u16	       :16;
	volatile u16	 CCR4	  ;
	volatile u16	       :16;
	volatile u32	 BDTR	  ;
	volatile u16	 DCR	  ;
	volatile u16	       :16;
	volatile u32	 DMAR	  ;
	


}TIM18_REGDef_t;

#define TIM1_u32_BASE_ADDRESS		 0x40012C00UL
#define TIM1		((volatile TIM18_REGDef_t*)TIM1_u32_BASE_ADDRESS)

#define TIM8_u32_BASE_ADDRESS		 0x40013400UL
#define TIM8		((volatile TIM18_REGDef_t*)TIM8_u32_BASE_ADDRESS)
/*****************************************************************/



#endif

