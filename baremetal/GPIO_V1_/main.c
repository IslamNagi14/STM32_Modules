/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 26/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : GPIO         ******************/
/*************************************************************/


#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"

#include"RCC_Int.h"

#include"GPIO_Int.h"

u32 x;
u32 y;
static u32 l;
int main(void)
{
	static u32 z;
	u16 Local_u16Counter;
	RCC_VidInitSysClk();

	RCC_enuStatePeripheralClk(IOPC,RCC_u8_ENABLE);


	const GPIO_PinCongig_t PC13 = {GPIO_u8GPIO_C,GPIO_u8PIN13,GPIO_u8Output10MHzPushPull};
	GPIO_enuSetPinMode(&PC13);

	///////////////////

	/* Loop forever */
	while(1)
	{

		GPIO_enuSetPinVal(&PC13,GPIO_u8LOW);


		for(Local_u16Counter =  0; Local_u16Counter <30000;Local_u16Counter++)
		{
			__asm("NOP");
		}

		GPIO_enuSetPinVal(&PC13,GPIO_u8HIGH);
		for(Local_u16Counter =  0; Local_u16Counter <40000;Local_u16Counter++)
		{
			__asm("NOP");
		}
	}
	return 0;
}
