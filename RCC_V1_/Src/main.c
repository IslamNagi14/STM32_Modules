/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : RCC          ******************/
/*************************************************************/

#include "StdTypes.h"
#include"BitMath.h"

#include"RCC_Int.h"

int main(void)
{
   RCC_VidInitSysClk();
   RCC_enuStatePeripheralClk(IOPA, RCC_u8_ENABLE);
   RCC_enuStateMCOpin(RCC_u8HIGH_SPEED_INTERNAL_CLOCK);
	while(1)
	{

	}
	return 0;
}
