/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 12/7/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : UART          ******************/
/*************************************************************/

#include"StdTypes.h"
#include"BitMath.h"
#include"GPIO/GPIO_Int.h"
#include"RCC/RCC_Int.h"
#include"UART1_Interface.h"
#include"STK/STK_interface.h"
int main(void)
{

	GPIO_PinCongig_t tx_pin = {GPIO_u8GPIO_A,GPIO_u8PIN9, APIO_u8Output2MHzPushPull};
	GPIO_PinCongig_t rx_pin = {GPIO_u8GPIO_A,GPIO_u8PIN10,GPIO_u8InputFloating};

	RCC_VidInitSysClk();
	RCC_enuStatePeripheralClk(RCC_u8IOPA, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8USART1, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8AFIO, RCC_u8_ENABLE);

	GPIO_enuSetPinMode(&tx_pin);
	GPIO_enuSetPinMode(&rx_pin);

	USART1_enuInit(Desable_ALL_INT, UART_9600);

	STK_vidInitSTK();


	/* Loop forever */
	for(;;)
	{

		USART1_enuSenchSendByte('A');
		STK_enuSyncDelay(1000000);
		USART1_enuSenchSendByte('B');
		STK_enuSyncDelay(1000000);
	}
}
