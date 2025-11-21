/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 12/7/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : UART          ******************/
/*************************************************************/

#ifndef UART1_INTERFACE_H_
#define UART1_INTERFACE_H_


#include"StdTypes.h"
#include"errorStatuse.h"


typedef enum
{
	UART_2400   = 0xD05,
	UART_4800   = 0x683,
	UART_9600   = 0x341,
	UART_115200 = 0x45,
}BaudRate_t;

typedef enum
{
	Desable_ALL_INT      = 0x00,
	Enable_TC_INT        = 0x40,
	Enable_RxNotE_INT    = 0x20,
	Enable_TC_RxNotE_INT = 0x60,
}UART_EN_Dis_INT_t;

/********************************    functions' protoypes        ****************************************/

ES_t USART1_enuInit(UART_EN_Dis_INT_t Copy_enuINTStatus , BaudRate_t Copy_enuBaudRate);
/*this function is used to send single byte (without interrupt)*/
ES_t USART1_enuSenchSendByte(u8 Copy_u8DataByte);

/*this function is used to send single byte (with interrupt)*/
ES_t USART1_enuAsenchSendByte(u8 Copy_u8DataByte);

/*this function is used to send single byte (without interrupt)*/
ES_t USART1_enuSenchSendStream(u8* Copy_pu8DataByte, u16 Copy_u16DataSize);

/*this function is used to receive single byte (without interrupt)*/
ES_t USART1_enuSenchRecvByte(u8* Copy_pu8DataByte);

/*this function is used to receive single byte (with interrupt)*/
ES_t USART1_enuAsenchRecvByte(u8* Copy_pu8DataByte);





/********************************************************************************************************/
#endif /* UART1_INTERFACE_H_ */
