/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 12/7/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : UART          ******************/
/*************************************************************/

#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"
#include"stm32f103xx.h"

#include"UART1_Private.h"
#include"UART1_Interface.h"



static u8 Global_u8TxCompleteFlag = 1;
static u8 Global_u8RxCompleteFlag = 0;


ES_t USART1_enuInit(UART_EN_Dis_INT_t Copy_enuINTStatus , BaudRate_t Copy_enuBaudRate)
{
	ES_t Local_enuErrorState = ES_NOK;

	USART1->CR1 = 0;
	USART1->CR2 = 0;
	SETBIT(USART1->CR1,13);// USART enable

	CLEARBIT(USART1->CR1,12);// Set word length = 8-bits

	USART1->CR1 |=  Copy_enuINTStatus;//set interrupt status

	USART1->BRR = Copy_enuBaudRate;//set baud rate vlaue

	CLEARBIT(USART1->CR1,3);// Transmitter enable
	SETBIT(USART1->CR1,2);// Receiver enable
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}
/*this function is used to send single byte (without interrupt)*/
ES_t USART1_enuSenchSendByte(u8 Copy_u8DataByte)
{
	ES_t Local_enuErrorState = ES_NOK;



	if(GETBIT(USART1->SR,7))// check data register is empty
	{


		USART1->DR = Copy_u8DataByte;// put data in data register

		while(!(GETBIT(USART1->SR,6)));// poll untile TC flag
		CLEARBIT(USART1->SR,6);// clear TC flag


	}

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

/*this function is used to send single byte (with interrupt)*/
ES_t USART1_enuAsenchSendByte(u8 Copy_u8DataByte)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Global_u8TxCompleteFlag)//check TCX flag
	{
		Global_u8TxCompleteFlag = 0;//reset TCX flag


		USART1->DR = Copy_u8DataByte;// put data in data register


		Local_enuErrorState = ES_OK;
	}



	return Local_enuErrorState;
}

/*this function is used to send single byte (without interrupt)*/
ES_t USART1_enuSenchSendStream(u8* Copy_pu8DataByte, u16 Copy_u16DataSize)
{
	ES_t Local_enuErrorState = ES_NOK;
	u16 Loacl_u16Iterator = 0;
	if(Copy_pu8DataByte)
	{
		for(Loacl_u16Iterator = 0 ;Loacl_u16Iterator < Copy_u16DataSize;Loacl_u16Iterator++)
		{
			if(GETBIT(USART1->SR,7))// check data register is empty
			{


				USART1->DR = *(Copy_pu8DataByte + Loacl_u16Iterator);// put data in data register

				while(!(GETBIT(USART1->SR,6)));// poll untile TC flag
				CLEARBIT(USART1->SR,6);// clear TC flag


			}
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}


	return Local_enuErrorState;
}

/*this function is used to receive single byte (without interrupt)*/
ES_t USART1_enuSenchRecvByte(u8 *Copy_Pu8DataByte)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_Pu8DataByte)
	{

		if(GETBIT(USART1->SR,5))//check data register empty or not
		{


			*Copy_Pu8DataByte = USART1->DR;// read data register

			CLEARBIT(USART1->SR,5);// clear RXNE flag


			Local_enuErrorState = ES_OK;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}

/*this function is used to receive single byte (with interrupt)*/
ES_t USART1_enuAsenchRecvByte(u8* Copy_Pu8DataByte)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Global_u8RxCompleteFlag)//check Rx new data  flag
	{
		Global_u8RxCompleteFlag = 0;// reset rx new data flag


		*Copy_Pu8DataByte = USART1->DR;// reading databyte

		CLEARBIT(USART1->SR, 5);//clear RXNE flag
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}


	return Local_enuErrorState;
}











void USART1_IRQHandler(void)
{
	if(GETBIT(USART1->SR, 6))//checking if the handler is due to data transmission
	{
		Global_u8TxCompleteFlag = 1;//data is transmitted

		/***********************
		 ***********************
		 ******function call****
		 ***********************
		 ***********************/


		CLEARBIT(USART1->SR, 6);//clear TC flag

	}
	else
	{

	}

	if(GETBIT(USART1->SR, 5))//checking if the handler is due to data receiving
	{
		Global_u8RxCompleteFlag = 1;//data is transmitted


		CLEARBIT(USART1->SR, 5);//clear RXNE flag
	}
	else
	{

	}

}
