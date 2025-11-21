/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 17/8/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : ADC1          ******************/
/*************************************************************/

#include"LIB/StdTypes.h"
#include"LIB/BitMath.h"
#include"LIB/errorStatuse.h"

#include"RCC/RCC_Int.h"
#include"STK/STK_interface.h"
#include"GPIO/GPIO_Int.h"
#include"ADC/ADC_Interface.h"

extern ADC1_Config_t ADC1_strConfig1;

int main(void)
{
	u16 Data[16];
	RCC_VidInitSysClk();
	STK_vidInitSTK();
	RCC_enuStatePeripheralClk(RCC_u8IOPA, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8IOPC, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8AFIO, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8ADC1, RCC_u8_ENABLE);

	GPIO_PinCongig_t LED_C13 = {GPIO_u8GPIO_C,GPIO_u8PIN13,GPIO_u8Output10MHzPushPull};
	GPIO_PinCongig_t AnaloginputChannel0 = {GPIO_u8GPIO_A,GPIO_u8PIN0,GPIO_u8InputAnalog};
	ChannelConfig_t ConfigOfChannel0 = {ADC1_u8Channel0,ADC1_239_5Cycle,ADC_u8_1stConversion};

	GPIO_enuSetPinMode(&AnaloginputChannel0);
	GPIO_enuSetPinMode(&LED_C13);
	ADC1_enuInit(&ADC1_strConfig1);
	ADC1_enuConfigRegularChannel(&ConfigOfChannel0);

	/* Loop forever */
	while(1)
	{
		ADC1_enuStartRegularConversionWithPolling(&ADC1_strConfig1,Data , 1);
		if( ((Data[0] * 3.3f)/4095) >= 3.2f)
			GPIO_enuSetPinVal(&LED_C13, GPIO_u8HIGH);
		else
		{
			GPIO_enuSetPinVal(&LED_C13, GPIO_u8LOW);
		}

	}

	return 0;
}
