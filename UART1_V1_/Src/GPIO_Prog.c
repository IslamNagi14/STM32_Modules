/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 26/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : GPIO          ******************/
/*************************************************************/

/*LIB*/
#include"StdTypes.h"
#include"errorStatuse.h"
#include"BitMath.h"
#include"stm32f103xx.h"

/* MCAL*/
#include"../Inc/GPIO/GPIO_Int.h"
#include"../Inc/GPIO/GPIO_Config.h"
#include"../Inc/GPIO/GPIO_Prive.h"

static GPIOx_REGDef_t *Private_AptrTostrOfGPIOx[] =
{
		GPIOA ,
		GPIOB ,
		GPIOC ,
};



ES_t GPIO_enuSetPinMode				(const GPIO_PinCongig_t * Copy_PstrPinConfig)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8PinMode = Copy_PstrPinConfig->PinMode;
	if(NULL != Copy_PstrPinConfig)
	{
		if(GPIO_u8GPIO_A <= Copy_PstrPinConfig->PortId && GPIO_u8GPIO_C >= Copy_PstrPinConfig->PortId)
		{
			if(GPIO_u8InputPullDown == Local_u8PinMode || GPIO_u8InputPullUp == Local_u8PinMode)
			{
				if(GETBIT(Local_u8PinMode,0))//if condition true it's pullup else it's pulldown
				{
					SETBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
					Local_u8PinMode--;
				}
				else
				{
					CLEARBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
				}

			}
			if(GPIO_u8PIN0 <= Copy_PstrPinConfig->PinId && GPIO_u8PIN7 >= Copy_PstrPinConfig->PinId)
			{
				//clear mode bits(4-its) to make it ready to configured
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->CRL &= ~(0xfUL<<(Copy_PstrPinConfig->PinId * 4)); //0xf = 0000 0000 0000 0000 0000 0000 0000 1111
				// set PIN mode
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->CRL |= (Local_u8PinMode<<(Copy_PstrPinConfig->PinId * 4));
				Local_enuErrorState = ES_OK;
			}
			else if (GPIO_u8PIN8 <= Copy_PstrPinConfig->PinId && GPIO_u8PIN15 >= Copy_PstrPinConfig->PinId)
			{
				//clear mode bits(4-its) to make it ready to configured
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->CRH &= ~(0xfUL<<((Copy_PstrPinConfig->PinId - 8)* 4)); //0xf = 0000 0000 0000 0000 0000 0000 0000 1111
				// set PIN mode
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->CRH |= (Local_u8PinMode<<((Copy_PstrPinConfig->PinId - 8) * 4));
				Local_enuErrorState = ES_OK;
			}
			else
			{
				Local_enuErrorState = ES_Out_Of_Range;
			}
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
ES_t GPIO_enuSetPinVal				(const GPIO_PinCongig_t * Copy_PstrPinConfig,GPIOx_Val_t Copy_enuPinVal)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NULL != Copy_PstrPinConfig)
	{
		if(GPIO_u8GPIO_A <= Copy_PstrPinConfig->PortId && GPIO_u8GPIO_C >= Copy_PstrPinConfig->PortId && GPIO_u8PIN0 <= Copy_PstrPinConfig->PinId && GPIO_u8PIN15 >= Copy_PstrPinConfig->PinId)
		{
			if( GPIO_u8HIGH == Copy_enuPinVal || GPIO_u8FLOAT == Copy_enuPinVal)
			{
				//SETBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId); //Non-atomic access
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->BSRR = (ONE << Copy_PstrPinConfig->PinId);//Atomic access with BSRRx
			}
			else if (GPIO_u8LOW == Copy_enuPinVal)
			{
				//CLEARBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);//Non-atomic access
				//Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->BSRR = (ONE << Copy_PstrPinConfig->PinId + 16);//Atomic access with BSRRx
				Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->BRR = (ONE << Copy_PstrPinConfig->PinId); //Atomic access with BRRx
			}
			else
			{
				Local_enuErrorState = ES_Out_Of_Range;
			}
		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}
ES_t GPIO_enuGetPinVal				(const GPIO_PinCongig_t * Copy_PstrPinConfig,u8 *Copy_pu8PinVal)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NULL != Copy_PstrPinConfig && NULL != Copy_pu8PinVal)
	{
		if(GPIO_u8PIN0 <= Copy_PstrPinConfig->PinId && GPIO_u8PIN15 >= Copy_PstrPinConfig->PinId && GPIO_u8GPIO_A <= Copy_PstrPinConfig->PortId && GPIO_u8GPIO_C >= Copy_PstrPinConfig->PortId)
		{
			if(GPIO_u8InputAnalog == Copy_PstrPinConfig->PinMode || GPIO_u8InputFloating == Copy_PstrPinConfig->PinMode || GPIO_u8InputPullDown == Copy_PstrPinConfig->PinMode || GPIO_u8InputPullUp == Copy_PstrPinConfig->PinMode)
				*Copy_pu8PinVal = GETBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->IDR,Copy_PstrPinConfig->PinId);
			else
				*Copy_pu8PinVal = GETBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);

		}
		else
			Local_enuErrorState = ES_Out_Of_Range;
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}
	return Local_enuErrorState;
}
ES_t GPIO_enuTogPinVal		        (const GPIO_PinCongig_t * Copy_PstrPinConfig)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_PstrPinConfig)
	{
		TOOGLEBIT(Private_AptrTostrOfGPIOx[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}


	return Local_enuErrorState;
}
