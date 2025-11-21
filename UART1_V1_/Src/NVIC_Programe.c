/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 30/6/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : NVIC         ******************/
/*************************************************************/

#include"StdTypes.h"
#include"errorStatuse.h"
#include"BitMath.h"
#include"stm32f103xx.h"

#include"NVIC/NVIC_Private.h"
#include"NVIC/NVIC_Config.h"
#include"NVIC/NVIC_Interface.h"

ES_t NVIC_enuEnableINT       (u8 Copy_u8PrephiralID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NVIC_u8_I2C1_EV >= Copy_u8PrephiralID)
	{

		SETBIT(NVIC->ISER[0],Copy_u8PrephiralID);
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_I2C1_ER <= Copy_u8PrephiralID && NVIC_u8_DMA2_Channel4_5 >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ISER[1],(Copy_u8PrephiralID - NVIC_u8_I2C1_ER));
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_CAN2_RX0 <= Copy_u8PrephiralID && NVIC_u8_OTG_FS >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ISER[2],(Copy_u8PrephiralID - NVIC_u8_CAN2_RX0));
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}


	return Local_enuErrorState;
}
ES_t NVIC_enuDisableINT      (u8 Copy_u8PrephiralID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NVIC_u8_I2C1_EV >= Copy_u8PrephiralID)
	{

		SETBIT(NVIC->ICER[0],Copy_u8PrephiralID);
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_I2C1_ER <= Copy_u8PrephiralID && NVIC_u8_DMA2_Channel4_5 >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ICER[1],(Copy_u8PrephiralID - NVIC_u8_I2C1_ER));
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_CAN2_RX0 <= Copy_u8PrephiralID && NVIC_u8_OTG_FS >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ICER[2],(Copy_u8PrephiralID - NVIC_u8_CAN2_RX0));
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}


ES_t NVIC_enuSetPendingINT   (u8 Copy_u8PrephiralID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NVIC_u8_I2C1_EV >= Copy_u8PrephiralID)
	{

		SETBIT(NVIC->ISPR[0],Copy_u8PrephiralID);
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_I2C1_ER <= Copy_u8PrephiralID && NVIC_u8_DMA2_Channel4_5 >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ISPR[1],(Copy_u8PrephiralID - NVIC_u8_I2C1_ER));
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_CAN2_RX0 <= Copy_u8PrephiralID && NVIC_u8_OTG_FS >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ISPR[2],(Copy_u8PrephiralID - NVIC_u8_CAN2_RX0));
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}
ES_t NVIC_enuClearPendingINT (u8 Copy_u8PrephiralID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(NVIC_u8_I2C1_EV >= Copy_u8PrephiralID)
	{

		SETBIT(NVIC->ICPR[0],Copy_u8PrephiralID);
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_I2C1_ER <= Copy_u8PrephiralID && NVIC_u8_DMA2_Channel4_5 >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ICPR[1], (Copy_u8PrephiralID - NVIC_u8_I2C1_ER));
		Local_enuErrorState = ES_OK;
	}
	else if(NVIC_u8_CAN2_RX0 <= Copy_u8PrephiralID && NVIC_u8_OTG_FS >= Copy_u8PrephiralID)
	{
		SETBIT(NVIC->ICPR[2],(Copy_u8PrephiralID - NVIC_u8_CAN2_RX0));
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}



	return Local_enuErrorState;
}


ES_t NVIC_enuGetINTStatues(u8 Copy_u8PrephiralID , u8* Copy_Pu8INTStatues)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_Pu8INTStatues)
	{
		if(NVIC_u8_I2C1_EV >= Copy_u8PrephiralID)
		{

			*Copy_Pu8INTStatues = GETBIT(NVIC->IABR[0],Copy_u8PrephiralID);
			Local_enuErrorState = ES_OK;
		}
		else if(NVIC_u8_I2C1_ER <= Copy_u8PrephiralID && NVIC_u8_DMA2_Channel4_5 >= Copy_u8PrephiralID)
		{
			*Copy_Pu8INTStatues = GETBIT(NVIC->IABR[1], (Copy_u8PrephiralID - NVIC_u8_I2C1_ER));
			Local_enuErrorState = ES_OK;
		}
		else if(NVIC_u8_CAN2_RX0 <= Copy_u8PrephiralID && NVIC_u8_OTG_FS >= Copy_u8PrephiralID)
		{
			*Copy_Pu8INTStatues = GETBIT(NVIC->IABR[2],(Copy_u8PrephiralID - NVIC_u8_CAN2_RX0));
			Local_enuErrorState = ES_OK;
		}
		else
		{
			Local_enuErrorState = ES_Out_Of_Range;
		}
	}
		return Local_enuErrorState;
	}


	ES_t NVIC_enuSetGroupPriority  (u8 Copy_u8PrephiralID , u8 Copy_u8GroupPriority)
	{
		ES_t Local_enuErrorState = ES_NOK;

		SCB_AIRCR = 0x05FA300;// Enable Priority Grouping

		if( 59 >= Copy_u8PrephiralID && 16 >= Copy_u8GroupPriority)
		{
			NVIC->IPR[Copy_u8PrephiralID / 4] &= ~(0X0000000FUL << (4 + 8 * (Copy_u8PrephiralID % 4)));
			NVIC->IPR[Copy_u8PrephiralID / 4] |= (Copy_u8GroupPriority << (4 + 8 * (Copy_u8PrephiralID % 4)));
			Local_enuErrorState = ES_OK;
		}


		return Local_enuErrorState;
	}
