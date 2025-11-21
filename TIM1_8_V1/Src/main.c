/**************************************************************/
/********************Name    : Islam Nagi	*******************/
/********************Date    : 22/8/2025    *******************/
/********************Version    : 1.0       *******************/
/********************SWC    : Timer(1 & 8)   ******************/
/**************************************************************/

#include"LIB/StdTypes.h"
#include"LIB/BitMath.h"
#include"LIB/errorStatuse.h"


#include"RCC/RCC_Int.h"
#include"GPIO/GPIO_Int.h"
#include"ADC/ADC_Interface.h"
#include"TIM18/TIM18_Interface.h"

extern ADC1_Config_t ADC1_strConfig1;

int main(void)
{
	u16 Data[16];u8 i = 100;
	RCC_VidInitSysClk();
	RCC_enuStatePeripheralClk(RCC_u8IOPA, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8IOPC, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8AFIO, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8ADC1, RCC_u8_ENABLE);
	RCC_enuStatePeripheralClk(RCC_u8TIM1, RCC_u8_ENABLE);

	GPIO_PinCongig_t LED_C13 = {GPIO_u8GPIO_C,GPIO_u8PIN13,GPIO_u8Output10MHzPushPull};
	GPIO_PinCongig_t AnaloginputChannel0 = {GPIO_u8GPIO_A,GPIO_u8PIN0,GPIO_u8InputAnalog};
	ChannelConfig_t ConfigOfChannel0 = {ADC1_u8Channel0,ADC1_239_5Cycle,ADC_u8_1stConversion};

	GPIO_PinCongig_t AnalogoutputChannel8 = {GPIO_u8GPIO_A,GPIO_u8PIN8,APIO_u8Output10MHzPushPull};// TIM CH1

	GPIO_enuSetPinMode(&AnaloginputChannel0);
	GPIO_enuSetPinMode(&AnalogoutputChannel8);
	GPIO_enuSetPinMode(&LED_C13);
	ADC1_enuInit(&ADC1_strConfig1);
	ADC1_enuConfigRegularChannel(&ConfigOfChannel0);
	TIM_enuPWM_Init(TIM1_ID, TIM_CHANNEL_1, 1000, TIM_PWM_EDGE_ALIGNED);
	TIM_enuPWM_SetDuty(TIM1_ID, TIM_CHANNEL_1, i);
	TIM_enuPWM_Start(TIM1_ID, TIM_CHANNEL_1);
	/* Loop forever */
	while(1)
	{


GPIO_enuSetPinVal(&LED_C13, GPIO_u8HIGH);
TIM_enuDelaySync_ms(TIM8_ID, 500);
GPIO_enuSetPinVal(&LED_C13, GPIO_u8LOW);
TIM_enuDelaySync_ms(TIM8_ID, 500);

//		for(i = 100;i>0;i--)
//		{
//			TIM_enuPWM_SetDuty(TIM1_ID, TIM_CHANNEL_1, i);
//			TIM_enuPWM_Start(TIM1_ID, TIM_CHANNEL_1);
//			TIM_enuDelaySync_ms(TIM8_ID, 500);
//		}
//		for(i = 0;i<100;i++)
//		{
//			TIM_enuPWM_SetDuty(TIM1_ID, TIM_CHANNEL_1, i);
//			TIM_enuPWM_Start(TIM1_ID, TIM_CHANNEL_1);
//			TIM_enuDelaySync_ms(TIM8_ID, 500);
//		}





		/*ADC1_enuStartRegularConversionWithPolling(&ADC1_strConfig1,Data , 1);
		if( ((Data[0] * 3.3f)/4095) >= 3.2f)
			GPIO_enuSetPinVal(&LED_C13, GPIO_u8HIGH);
		else
		{
			GPIO_enuSetPinVal(&LED_C13, GPIO_u8LOW);
		}*/

	}

	return 0;
}
