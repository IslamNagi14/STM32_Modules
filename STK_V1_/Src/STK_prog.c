/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 10/5/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : STK           ******************/
/*************************************************************/


/*LIB*/
#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"
#include"stm32f103xx.h"
/*MCAL*/
#include"STK_private.h"
#include"STK_interface.h"
#include"STK_config.h"

/*Global pointer to function*/
volatile static void (*GlobalP2FUN)(void) = NULL;

/*Global flag*/
volatile static u8 Global_u8ASynchtype ;

void STK_vidInitSTK                (void)//set prescaleing + disable STK
{
#if STK_u8ProcessorClock == STK_u8ClockSource
	SETBIT(SYSTICK->CTRL,STK_u8CLKSOURCE);
#elif STK_u8ProcessorClockDiv8 == STK_u8ClockSource
	CLEARBIT(SYSTICK->CTRL,STK_u8CLKSOURCE);
#else
#error"Wrong prescaling"

#endif
	CLEARBIT(SYSTICK->CTRL,STK_u8ENCOUNT);//disable SYSTICK
	CLEARBIT(SYSTICK->CTRL,STK_u8TICKINT);//disable interrupt
}
/*                Synch function                  */
ES_t STK_enuSyncDelay               (u32 Copy_u32DelyedTime)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(0x00ffffff >= Copy_u32DelyedTime)
	{

		SYSTICK->LOAD = Copy_u32DelyedTime;             //input load value
		SETBIT(SYSTICK->CTRL,STK_u8ENCOUNT);            //enable SYSTICK timer
		while(!GETBIT(SYSTICK->CTRL,STK_u8COUNTFLAG));  //polling delay
		CLEARBIT(SYSTICK->CTRL,STK_u8ENCOUNT);          //Disable SYSTICK timer

		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}
/*                ASynch function                  */
ES_t STK_enuASyncDelaySingleShot    (u32 Copy_u32DelyedTime,void (*Copy_pf)(void))
{
	ES_t Local_enuErrorState = ES_NOK;
	if(0x00ffffff >= Copy_u32DelyedTime && NULL != Copy_pf)
	{

		SYSTICK->LOAD = Copy_u32DelyedTime;//input load value

		SETBIT(SYSTICK->CTRL,STK_u8ENCOUNT);//enable SYSTICK timer

		SETBIT(SYSTICK->CTRL,STK_u8TICKINT);//enable interrupt

		GlobalP2FUN = Copy_pf;//set call back
		Global_u8ASynchtype = STK_u8singleShot;// for single shot

		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}
ES_t STK_enuASyncDelayMultiShot     (u32 Copy_u32DelyedTime,void (*Copy_pf)(void))
{
	ES_t Local_enuErrorState = ES_NOK;
	if(0x00ffffff >= Copy_u32DelyedTime && NULL != Copy_pf)
	{

		SYSTICK->LOAD = Copy_u32DelyedTime - ONE;//input load value

		SETBIT(SYSTICK->CTRL,STK_u8ENCOUNT);//enable SYSTICK timer

		SETBIT(SYSTICK->CTRL,STK_u8TICKINT);//enable interrupt

		GlobalP2FUN = Copy_pf;//set call back

		Global_u8ASynchtype = STK_u8MultiShot;// for multi shot

		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}


ES_t STK_enuStopTimer               (void)
{
	ES_t Local_enuErrorState = ES_NOK;
	CLEARBIT(SYSTICK->CTRL,STK_u8ENCOUNT);//disable timer
	SYSTICK->VAL = ZERO;
	SYSTICK->LOAD = ZERO;
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}
ES_t STK_enuGetElapsedTime          (u32 *Copy_Pu32ElapsedTime)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_Pu32ElapsedTime)
	{

		*Copy_Pu32ElapsedTime = SYSTICK->LOAD - SYSTICK->VAL;

		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}
ES_t STK_enuGetRemainingTime        (u32 *Copy_Pu32RemainingTime)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_Pu32RemainingTime)
	{
		*Copy_Pu32RemainingTime = SYSTICK->VAL;
		Local_enuErrorState = ES_OK;
	}
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}




void SysTick_Handler(void)
{
	if(NULL != GlobalP2FUN)
	{
		if(STK_u8MultiShot == Global_u8ASynchtype)
		{

		}
		else if (STK_u8singleShot == Global_u8ASynchtype)
		{
			SYSTICK->LOAD = ZERO;
			CLEARBIT(SYSTICK->CTRL,STK_u8ENCOUNT);//Disable SYSTICK timer
			CLEARBIT(SYSTICK->CTRL,STK_u8TICKINT);//Disable interrupt
		}

		SYSTICK->VAL = ZERO;// clear COUNTFLAG as mentioned in program manual
		GlobalP2FUN();
	}
}
