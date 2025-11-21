/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : RCC          ******************/
/*************************************************************/

/*LIB*/
#include"LIB/StdTypes.h"
#include"LIB/errorStatuse.h"
#include"LIB/BitMath.h"
#include"LIB/stm32f103xx.h"

/* MCAL*/
#include"RCC/RCC_Int.h"
#include"RCC/RCC_Config.h"
#include"RCC/RCC_Prive.h"


void RCC_VidInitSysClk(void)
{

	CLEARBIT(RCC->CFGR,0); CLEARBIT(RCC->CFGR,1);

#if RCC_U8_CLK_SYS == HIGH_SPEED_INTERNAL_CLOCK

	while(!GETBIT(RCC->CR,1));

	SETBIT(RCC->CR,0);//enable hsi
	CLEARBIT(RCC->CFGR,0); CLEARBIT(RCC->CFGR,1);//select HSI as a system clk source

#elif RCC_U8_CLK_SYS == HIGH_SPEED_EXTERNAL_CLOCK

#if EXT_SOURCE_TYPE == CERAMIC_CRYSTAL

	CLEARBIT(RCC->CR,18);

#elif EXT_SOURCE_TYPE == RC

	SETBIT(RCC->CR,18);
#endif
	while(!GETBIT(RCC->CR,17));
	SETBIT(RCC->CR,16);

	SETBIT(RCC->CFGR,0);//HSE selected as a sys clk



#elif RCC_U8_CLK_SYS == PHASE_LOCKED_LOOP_CLOCK

	while(!GETBIT(RCC->CR,25));
	SETBIT(RCC->CR,24);//enable pll

#if PLL_ENTRY_CLK == RCC_u8HIGH_SPEED_INTERNAL_CLOCK

	while(!GETBIT(RCC->CR,1));
	SETBIT(RCC->CR,0); //enable HSI
	CLEARBIT(RCC->CFGR,16);//select HSI as input for pll

#elif	PLL_ENTRY_CLK == RCC_u8HIGH_SPEED_EXTERNAL_CLOCK


#if EXT_SOURCE_TYPE == CERAMIC_CRYSTAL
	CLEARBIT(RCC->CR,18);
#if	((HSE_DIVIDED_FACTOR == 2 && PLL_MUL_FACTOR > 9) || (HSE_DIVIDED_FACTOR == 1 && PLL_MUL_FACTOR > 4))
#error	" The PLL output frequency exceed 72MHz"
#endif
#elif EXT_SOURCE_TYPE == RC
#if	((HSE_DIVIDED_FACTOR == 2 && PLL_MUL_FACTOR > 5) || (HSE_DIVIDED_FACTOR == 1 && PLL_MUL_FACTOR > 2))
#error	" The PLL output frequency exceed 72MHz"
#endif
	SETBIT(RCC->CR,18);
#endif

	while(!GETBIT(RCC->CR,17));
	SETBIT(RCC->CR,16);//enable HSE

#if HSE_DIVIDED_FACTOR == 1
	CLEARBIT(RCC->CFGR,17);
#elif HSE_DIVIDED_FACTOR == 2
	SETBIT(RCC->CFGR,17);
#endif
	SETBIT(RCC->CFGR,16);//select HSE as input for pll

#endif
	RCC->CFGR &= ~(0xf<<18);
	RCC->CFGR |= ((PLL_MUL_FACTOR-2)<<18); //mul factor


	SETBIT(RCC->CFGR,1);//pll selected as a sys clk

#else
#error"Wrong selection"
#endif
}
ES_t RCC_enuStatePeripheralClk(u8 Copy_u8Peripheral,u8 Copy_u8State)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8Peripheral>=DMA1 && Copy_u8Peripheral<= SDIO)
	{
		if(ENABLE == Copy_u8State)
		{
			SETBIT(RCC->AHBENR,Copy_u8Peripheral);
			Local_enuErrorState = ES_OK;
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->AHBENR,Copy_u8Peripheral);
			Local_enuErrorState = ES_OK;
		}
	}
	else if (Copy_u8Peripheral>=AFIO && Copy_u8Peripheral<= TIM11)
	{

		if(ENABLE == Copy_u8State)
		{
			SETBIT(RCC->APB2ENR,(Copy_u8Peripheral-AFIO));
			Local_enuErrorState = ES_OK;
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->APB2ENR,(Copy_u8Peripheral-AFIO));
			Local_enuErrorState = ES_OK;
		}
	}
	else if (Copy_u8Peripheral>=TIM2 && Copy_u8Peripheral<= DAC)
	{
		if(ENABLE == Copy_u8State)
		{
			SETBIT(RCC->APB1ENR,(Copy_u8Peripheral-TIM2));
			Local_enuErrorState = ES_OK;
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->APB1ENR,(Copy_u8Peripheral-TIM2));
			Local_enuErrorState = ES_OK;
		}

	}

	return Local_enuErrorState;
}
ES_t RCC_enuStateMCOpin(u8 Copy_u8SelectedClock)
{
	ES_t Local_enuErroeState = ES_NOK;
	if((NO_CLOCK == Copy_u8SelectedClock) || (SYS_CLOCK == Copy_u8SelectedClock) || (HSI == Copy_u8SelectedClock) || (HSE == Copy_u8SelectedClock
	) || (PLL == Copy_u8SelectedClock))
	{
		if(HSI == Copy_u8SelectedClock)
		{
			while(!GETBIT(RCC->CR,1));
			SETBIT(RCC->CR,0);
			Local_enuErroeState = ES_OK;
		}

		else if (HSE == Copy_u8SelectedClock)
		{
			if (EXT_SOURCE_TYPE == CERAMIC_CRYSTAL)
			{
				CLEARBIT(RCC->CR,18);
			}
			else if (EXT_SOURCE_TYPE == RC)
			{
				SETBIT(RCC->CR,18);
			}

			while(!GETBIT(RCC->CR,17));
			SETBIT(RCC->CR,16);
			Local_enuErroeState = ES_OK;
		}
		else if(PLL == Copy_u8SelectedClock)
		{
			while(!GETBIT(RCC->CR,25));
			SETBIT(RCC->CR,24);//enable pll

			if (PLL_ENTRY_CLK == RCC_u8HIGH_SPEED_INTERNAL_CLOCK)
			{
				while(!GETBIT(RCC->CR,1));
				SETBIT(RCC->CR,0); //enable HSI
				CLEARBIT(RCC->CFGR,16);//select HSI as input for pll
			}
			else if	(PLL_ENTRY_CLK == RCC_u8HIGH_SPEED_EXTERNAL_CLOCK)
			{

				if (EXT_SOURCE_TYPE == CERAMIC_CRYSTAL)
				{
					if	((HSE_DIVIDED_FACTOR == 2 && PLL_MUL_FACTOR > 9) || (HSE_DIVIDED_FACTOR == 1 && PLL_MUL_FACTOR > 4))
						return Local_enuErroeState = ES_NOK;

					CLEARBIT(RCC->CR,18);
				}
				else if (EXT_SOURCE_TYPE == RC)
				{
					if	((HSE_DIVIDED_FACTOR == 2 && PLL_MUL_FACTOR > 5) || (HSE_DIVIDED_FACTOR == 1 && PLL_MUL_FACTOR > 2))
						return Local_enuErroeState = ES_NOK;
					SETBIT(RCC->CR,18);
				}

				while(!GETBIT(RCC->CR,17));
				SETBIT(RCC->CR,16);//enable HSE

				if (HSE_DIVIDED_FACTOR == 1)
				{
					CLEARBIT(RCC->CFGR,17);
				}
				else if (HSE_DIVIDED_FACTOR == 2)
				{
					SETBIT(RCC->CFGR,17);
				}
				SETBIT(RCC->CFGR,16);//select HSE as input for pll
			}


			RCC->CFGR &= ~(0xf<<18);
			RCC->CFGR |= ((PLL_MUL_FACTOR-2)<<18); //mul factor
			Local_enuErroeState = ES_OK;
		}

		RCC->CFGR |= Copy_u8SelectedClock<<MCO0;
		Local_enuErroeState = ES_OK;
	}

	return Local_enuErroeState;
}

ES_t RCC_enuStateCLKSecuritySys(u8 Copy_u8State)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(GETBIT(RCC->CR,17) && ENABLE == Copy_u8State)
	{
		SETBIT(RCC->CR,19);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		CLEARBIT(RCC->CR,19);
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t RCC_enuTrimHSI	(u32 Copy_u32TrimValKHz)
{
	ES_t Local_enuErrorState = ES_NOK;
	CLEARBIT(RCC->CR,7);
	Copy_u32TrimValKHz /= 40UL;  //40KHz
	Copy_u32TrimValKHz += 16UL;
	RCC->CR |= (Copy_u32TrimValKHz<<3);

	return Local_enuErrorState = ES_OK;
}

ES_t RCC_enuStateClkSourceInterrupt			(u8 Copy_u8CLKsource,u8 Copy_u8State)
{
	ES_t Local_enuErrorState = ES_NOK;


	switch(Copy_u8CLKsource)
	{

	case HSI:
		if(ENABLE == Copy_u8State)
		{
			while(!GETBIT(RCC->CIR,2));
			SETBIT(RCC->CIR,18);
			SETBIT(RCC->CIR,10);
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->CIR,10);
		}
		Local_enuErrorState = ES_OK;
		break;
	case HSE:
		if(ENABLE == Copy_u8State)
		{
			while(!GETBIT(RCC->CIR,3));
			SETBIT(RCC->CIR,19);
			SETBIT(RCC->CIR,11);
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->CIR,11);
		}
		Local_enuErrorState = ES_OK;
		break;
	case PLL:
		if(ENABLE == Copy_u8State)
		{
			while(!GETBIT(RCC->CIR,4));
			SETBIT(RCC->CIR,20);
			SETBIT(RCC->CIR,12);
		}
		else if (DISABLE == Copy_u8State)
		{
			CLEARBIT(RCC->CIR,12);
		}
		Local_enuErrorState = ES_OK;
		break;

	}

	return Local_enuErrorState;
}

ES_t RCC_enuResetPeripheral				(u8 Copy_u8Peripheral)
{

	ES_t Local_enuErrorState = ES_NOK;


	 if (Copy_u8Peripheral>=AFIO && Copy_u8Peripheral<= TIM11)
	{

		SETBIT(RCC->APB2RSTR,(Copy_u8Peripheral-AFIO));
		Local_enuErrorState = ES_OK;
	}
	else if (Copy_u8Peripheral>=TIM2 && Copy_u8Peripheral<= DAC)
	{
		SETBIT(RCC->APB1RSTR,(Copy_u8Peripheral-TIM2));
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
