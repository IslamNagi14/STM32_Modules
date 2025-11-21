/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 1/7/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : EXTI         ******************/
/*************************************************************/

#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"
#include"stm32f103xx.h"

#include"EXTI_Private.h"
#include"EXTI_Interface.h"



static volatile void (*EXTI_AVidPtr2Fun[7])(void) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};


ES_t EXTI_enuSetINTStatus(const EXTI_DefEXTI_t* Copy_pu8EINT)//set edge level and set the EXTI[enabled == Not masked] or [disabled == masked]
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8EINT)
	{


		switch(Copy_pu8EINT->EXTI_State)
		{
		case EXTI_u8_Enable:
			SETBIT(EXTI->IMR , Copy_pu8EINT->EXTI_ID);
			Local_enuErrorState = ES_OK;
			break;
		case EXTI_u8_Disable:
			CLEARBIT(EXTI->IMR , Copy_pu8EINT->EXTI_ID);
			Local_enuErrorState = ES_OK;
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}

		switch(Copy_pu8EINT->EXTI_EdgeType)
		{

		case EXTI_u8_Rising_Edge:
			SETBIT(EXTI->RTSR , Copy_pu8EINT->EXTI_ID);
			CLEARBIT(EXTI->FTSR , Copy_pu8EINT->EXTI_ID);
			Local_enuErrorState = ES_OK;
			break;
		case EXTI_u8_Falling_Edge:
			SETBIT(EXTI->FTSR , Copy_pu8EINT->EXTI_ID);
			CLEARBIT(EXTI->RTSR , Copy_pu8EINT->EXTI_ID);
			Local_enuErrorState = ES_OK;
			break;
		case EXTI_u8_Rising_Falling_Edge:
			SETBIT(EXTI->RTSR , Copy_pu8EINT->EXTI_ID);
			SETBIT(EXTI->FTSR , Copy_pu8EINT->EXTI_ID);
			Local_enuErrorState = ES_OK;
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}



	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}


	return Local_enuErrorState;
}

ES_t EXTI_enuEnableINT(EXTIs Copy_u8INT_ID)//Enable EXTIx
{
	ES_t Local_enuErrorState = ES_NOK;

	if(15 >= Copy_u8INT_ID)
	{
		SETBIT(EXTI->IMR , Copy_u8INT_ID);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuDisableINT(EXTIs Copy_u8INT_ID)//Disable EXTIx
{
	ES_t Local_enuErrorState = ES_NOK;

	if(15 >= Copy_u8INT_ID)
	{
		CLEARBIT(EXTI->IMR , Copy_u8INT_ID);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}

ES_t EXTI_enuClearINTPending(EXTIs Copy_u8INT_ID)//clear pending
{
	ES_t Local_enuErrorState = ES_NOK;

	if(15 >= Copy_u8INT_ID)
	{
		SETBIT(EXTI->PR , Copy_u8INT_ID);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}
ES_t EXTI_enuIsINTActive(EXTIs Copy_u8INT_ID , u8* Copy_pu8EXTI_Status)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pu8EXTI_Status)
	{
		if(15 >= Copy_u8INT_ID)
		{
			*Copy_pu8EXTI_Status =  GETBIT(EXTI -> PR , Copy_u8INT_ID);
			Local_enuErrorState = ES_OK;
		}
		else
		{
			Local_enuErrorState = ES_Out_Of_Range;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuGenerate_SW_INT(EXTIs Copy_u8INT_ID)
{
	ES_t Local_enuErrorState = ES_NOK;


	if(15 >= Copy_u8INT_ID)
	{
		SETBIT(EXTI->SWIER , Copy_u8INT_ID);
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}







ES_t EXTI_enuSetCallBackFun(EXTIs Copy_u8INT_ID , void (*Copy_P2Fun)(void))
{

	ES_t Local_enuErrorState = ES_NOK;


	if(EXTI_u8_LINE4 >= Copy_u8INT_ID)
	{

		EXTI_AVidPtr2Fun[Copy_u8INT_ID] = Copy_P2Fun;
		Local_enuErrorState = ES_OK;
	}
	else if(9 >= Copy_u8INT_ID)
	{
		EXTI_AVidPtr2Fun[EXTI_u8_LINE5_9] = Copy_P2Fun;
		Local_enuErrorState = ES_OK;
	}
	else if(15 >= Copy_u8INT_ID)
	{
		EXTI_AVidPtr2Fun[EXTI_u8_LINE10_15] = Copy_P2Fun;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;

}



void EXTI0_IRQHandler(void)
{
	SETBIT(EXTI -> PR , EXTI_u8_LINE0);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE0])
	{
		EXTI_AVidPtr2Fun[EXTI_u8_LINE0]();
	}
}
void EXTI1_IRQHandler(void)
{
	SETBIT(EXTI -> PR , EXTI_u8_LINE1);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE1])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE1]();
		}
}
void EXTI2_IRQHandler(void)
{
	SETBIT(EXTI -> PR , EXTI_u8_LINE2);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE2])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE2]();
		}
}
void EXTI3_IRQHandler(void)
{
	SETBIT(EXTI -> PR , EXTI_u8_LINE3);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE3])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE3]();
		}
}
void EXTI4_IRQHandler(void)
{
	SETBIT(EXTI -> PR , EXTI_u8_LINE4);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE4])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE4]();
		}
}
void EXTI9_5_IRQHandler(void)
{
	EXTI -> PR |= (0x1F << 5);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE5_9])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE5_9]();
		}
}
void EXTI15_10_IRQHandler(void)
{
	EXTI -> PR |= (0x3F << 10);
	if(EXTI_AVidPtr2Fun[EXTI_u8_LINE10_15])
		{
			EXTI_AVidPtr2Fun[EXTI_u8_LINE10_15]();
		}
}


