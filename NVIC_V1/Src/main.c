/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 30/6/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : NVIC         ******************/
/*************************************************************/

#include"StdTypes.h"
#include"errorStatuse.h"
#include"BitMath.h"

#include"RCC/RCC_Int.h"
#include"RCC/RCC_Config.h"

#include"STK/STK_interface.h"
#include"STK/STK_config.h"

#include"GPIO/GPIO_Int.h"
#include"GPIO/GPIO_Config.h"

#include"NVIC_Interface.h"
#include"NVIC_Config.h"

GPIO_PinCongig_t PC13 = {GPIO_u8GPIO_C,GPIO_u8PIN13,GPIO_u8Output10MHzPushPull};
int main(void)
{
	RCC_VidInitSysClk();
	STK_vidInitSTK();
	RCC_enuStatePeripheralClk(IOPC, RCC_u8_ENABLE);

	GPIO_enuSetPinMode(&PC13);
	NVIC_enuEnableINT(EXTI0);
	/* Loop forever */
	for(;;)
	{
		NVIC_enuSetPendingINT(EXTI0);
		STK_enuSyncDelay(1000000);

	}
}

void EXTI0_IRQHandler(void)
{
	NVIC_enuClearPendingINT(EXTI0);
	GPIO_enuTogPinVal(&PC13);
}
