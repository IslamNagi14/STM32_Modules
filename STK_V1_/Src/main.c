/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 10/5/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : STK           ******************/
/*************************************************************/

#include "../Inc/StdTypes.h"      // Get standerd type
#include "../Inc/errorStatuse.h"  // Get error statuse
#include "../Inc/BitMath.h"		  // Get BitMath lib


#include "RCC/RCC_Int.h"	  // RCC interface

#include "GPIO/GPIO_Int.h" // GPIO interface

#include "STK_interface.h" // SYSTICK interface




int main(void)
{
	u8 Local_u8Iterator;
 	RCC_VidInitSysClk();
	STK_vidInitSTK();
	RCC_enuStatePeripheralClk(IOPA, RCC_u8_ENABLE);

	GPIO_PinCongig_t Leds[4] = {
			{GPIO_u8GPIO_A,GPIO_u8PIN0,GPIO_u8Output2MHzPushPull},
			{GPIO_u8GPIO_A,GPIO_u8PIN1,GPIO_u8Output2MHzPushPull},
			{GPIO_u8GPIO_A,GPIO_u8PIN2,GPIO_u8Output2MHzPushPull},
			{GPIO_u8GPIO_A,GPIO_u8PIN3,GPIO_u8Output2MHzPushPull},
	};
	for(Local_u8Iterator = 0 ; 4 > Local_u8Iterator ; Local_u8Iterator++)
		GPIO_enuSetPinMode(Leds + Local_u8Iterator );

	/* Loop forever */
	while(ONE)
	{
		for(Local_u8Iterator = 0 ; 4 > Local_u8Iterator ; Local_u8Iterator++)
		{
			GPIO_enuSetPinVal(Leds + Local_u8Iterator, GPIO_u8HIGH);
			if(Local_u8Iterator > ZERO)
			GPIO_enuSetPinVal(Leds + Local_u8Iterator - ONE, GPIO_u8LOW);
			STK_enuSyncDelay(50000);
		}
		for( ; 0 < Local_u8Iterator ; Local_u8Iterator--)
		{
			GPIO_enuSetPinVal(Leds + Local_u8Iterator - ONE, GPIO_u8HIGH);
			if(Local_u8Iterator < 4)
			GPIO_enuSetPinVal(Leds + Local_u8Iterator , GPIO_u8LOW);
			STK_enuSyncDelay(50000);
		}

	}
}
