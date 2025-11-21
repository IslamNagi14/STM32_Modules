/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 1/7/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : EXTI         ******************/
/*************************************************************/

#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"

#include"RCC/RCC_Int.h"

#include"GPIO/GPIO_Int.h"
#include"NVIC/NVIC_Interface.h"
#include"STK/STK_interface.h"
#include"EXTI_Interface.h"

GPIO_PinCongig_t PC13 = {GPIO_u8GPIO_C , GPIO_u8PIN13 , GPIO_u8Output10MHzPushPull};
GPIO_PinCongig_t PA0 = {GPIO_u8GPIO_A , GPIO_u8PIN0 , GPIO_u8InputPullUp};
EXTI_DefEXTI_t Local_strEXTI0 = {EXTI_u8_LINE0 , EXTI_u8_Enable , EXTI_u8_Falling_Edge};
void tog(void)
{
	GPIO_enuTogPinVal(&PC13);
	return;
}

int main(void)
{
 	RCC_VidInitSysClk();
	RCC_enuStatePeripheralClk(IOPC, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(IOPA, RCC_u8_ENABLE);

	GPIO_enuSetPinMode(&PC13);
	GPIO_enuSetPinMode(&PA0);
	STK_vidInitSTK();
	EXTI_DefEXTI_t Local_strEXTI0 = {EXTI_u8_LINE0 , EXTI_u8_Enable , EXTI_u8_Falling_Edge};
	NVIC_enuEnableINT(EXTI0);
	EXTI_enuSetCallBackFun(EXTI_u8_LINE0, tog);

	EXTI_enuSetINTStatus(&Local_strEXTI0);

    /* Loop forever */
	for(;;);
}
