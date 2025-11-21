/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 17/8/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : ADC1          ******************/
/*************************************************************/

#include"LIB/StdTypes.h"
#include"LIB/BitMath.h"
#include"LIB/errorStatuse.h"
#include"LIB/stm32f103xx.h"

#include"ADC/ADC_Interface.h"
#include"ADC/ADC_Private.h"
#include"ADC/ADC_Config.h"



static volatile void (*ADC1_AVidPtr2Fun[5])(void) = {NULL,NULL,NULL,NULL,NULL};


ES_t ADC1_enuInit(ADC1_Config_t * Copy_PstrADC1Config)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_PstrADC1Config)
	{
		/* reset control registers 1 & 2*/
		ADC1->CR1 = 0;
		ADC1->CR2 = 0;

		ADC1->CR1 |= (Copy_PstrADC1Config->DualMode <<16);//set dual mode
		ADC1->CR1 |= (Copy_PstrADC1Config->Scan_SinglChannel <<8);// enable scan_disabe singleChannel or disable scan_enable singleChannel

		ADC1->CR2 |= (Copy_PstrADC1Config->continuousConv <<1);// SingleConversionMode or ContinuousMode
		ADC1->CR2 |= (Copy_PstrADC1Config->dataAlign <<11);// right or left

		if(Copy_PstrADC1Config->RegularExtriggerConvState == ADC1_u8Enable)
		{
			ADC1->CR2 |= (Copy_PstrADC1Config->RegularExtTrigger <<17);
			SETBIT(ADC1->CR2,20);
		}
		else if(Copy_PstrADC1Config->RegularExtriggerConvState == ADC1_u8Disable)
		{
			/* Do Nothing */
		}
		else
		{
			Local_enuErrorState = ES_Out_Of_Range;
		}
		if(Copy_PstrADC1Config->InjectedExtriggerConvState == ADC1_u8Enable)
		{
			ADC1->CR2 |= (Copy_PstrADC1Config->InjectedExtTrigger <<12);
			SETBIT(ADC1->CR2,15);
		}
		else if(Copy_PstrADC1Config->InjectedExtriggerConvState == ADC1_u8Disable)
		{
			/* Do Nothing */
		}
		else
		{
			Local_enuErrorState = ES_Out_Of_Range;
		}

		ADC1->HTR = 4095; // set maximum limit of all channels for WatchDog
		ADC1->LTR = ZERO;  // set lowest limit of all channels for WatchDog(ZERO)
		CLEARBIT(ADC1->CR1,9);// set WatchDog for all channels


		SETBIT(ADC1->CR2,ZERO);// enable adc1

		SETBIT(ADC1->CR2,3);//Reset calibration
		while(GETBIT(ADC1->CR2,3));//polling until Reset calibration completed

		SETBIT(ADC1->CR2,2);//calibration
		while(GETBIT(ADC1->CR2,2));//polling until calibration completed
	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}
ES_t ADC1_enuConfigRegularChannel(ChannelConfig_t * Copy_PstrChannelConfig)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_PstrChannelConfig)
	{
		if(9 >= Copy_PstrChannelConfig->ChannelID)
		{
			/*for SMPR2: startBit of channel = 3 * ChannelID */
			ADC1->SMPR2 &= ~(0x7 <<(3 * Copy_PstrChannelConfig->ChannelID)); // reset the sampleTime
			ADC1->SMPR2 |= (Copy_PstrChannelConfig->SampleTime <<(3 * Copy_PstrChannelConfig->ChannelID)); // set the new sampleTime
		}
		else if(17 >= Copy_PstrChannelConfig->ChannelID)
		{
			/*for SMPR1: startBit of channel = 3 *( ChannelID - 10)*/
			ADC1->SMPR1 &= ~(0x7 <<(3 * (Copy_PstrChannelConfig->ChannelID - 10 ))); // reset the sampleTime
			ADC1->SMPR1 |= (Copy_PstrChannelConfig->SampleTime <<(3 * (Copy_PstrChannelConfig->ChannelID - 10 ))); // set the new sampleTime
		}
		else
		{
			Local_enuErrorState  = ES_Out_Of_Range;
		}


		if(6 >= Copy_PstrChannelConfig->Rank)
		{
			/*for SQR3: startBit of Rank = 5 * (Rank-1) */
			ADC1->SQR3 &= ~(0x1f << (5 * (Copy_PstrChannelConfig->Rank - 1)));// reset the Rank
			ADC1->SQR3 |= (Copy_PstrChannelConfig->ChannelID << (5 * (Copy_PstrChannelConfig->Rank - 1)));// set the Rank
		}
		else if(12 >= Copy_PstrChannelConfig->Rank)
		{
			/*for SQR2: startBit  = 5 * (Rank-7) */
			ADC1->SQR2 &= ~(0x1f << (5 * (Copy_PstrChannelConfig->Rank - 7)));// reset the Rank
			ADC1->SQR2 |= (Copy_PstrChannelConfig->ChannelID << (5 * (Copy_PstrChannelConfig->Rank - 7)));// set the Rank
		}
		else if(16 >= Copy_PstrChannelConfig->Rank)
		{
			/*for SQR1: startBit  = 5 * (Rank-13) */
			ADC1->SQR1 &= ~(0x1f << (5 * (Copy_PstrChannelConfig->Rank - 13)));// reset the Rank
			ADC1->SQR1 |= (Copy_PstrChannelConfig->ChannelID << (5 * (Copy_PstrChannelConfig->Rank - 13)));// set the Rank
		}
		else
		{
			Local_enuErrorState  = ES_Out_Of_Range;
		}

	}
	else
	{
		Local_enuErrorState = ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}

ES_t ADC1_enuStartRegularConversionWithPolling(ADC1_Config_t * Copy_PstrADC1Config, u16 Copy_Pu16Data[16] , u8 Copy_u8SeqLength)
{
	ES_t Local_enuErrorState = ES_OK;
	u8 Local_u8Iterator = 0;
	ADC1->SQR1 &= ~(0xF<<20);// reset sequence length
	if(ONE >= Copy_u8SeqLength)
	{
		CLEARBIT(ADC1->CR1,8);//disable scan mode
	}
	else if(16 >= Copy_u8SeqLength)
	{
		SETBIT(ADC1->CR1,8);//enable scan mode
		ADC1->SQR1 |= (((Copy_u8SeqLength - 1) & 0xF)<<20);//set sequence length
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	if(ADC1_u8EXT_TRIG_SWSTART == Copy_PstrADC1Config->RegularExtTrigger)
	{
		SETBIT(ADC1->CR2,22);// Software start conversion of regular channels
	}

	if(ZERO == Copy_u8SeqLength)
	{
		while(!(GETBIT(ADC1->SR,1)));      // wait EOC
		Copy_Pu16Data[0] = ADC1->DR;  // read each conversion
	}
	else
	{
		for(Local_u8Iterator = 0; Local_u8Iterator < Copy_u8SeqLength; Local_u8Iterator++)
		{
			while(!(GETBIT(ADC1->SR,1)));      // wait EOC
			Copy_Pu16Data[Local_u8Iterator] = ADC1->DR;  // read each conversion
		}
	}

	return Local_enuErrorState;
}
ES_t ADC1_enuStartRegularConversionWithINT(ADC1_Config_t * Copy_PstrADC1Config, u8 Copy_u8SeqLength)
{
	ES_t Local_enuErrorState = ES_OK;
	CLEARBIT(ADC1->SR, 1);   // EOC = 0, clear regular end of conversion flag
	ADC1->SQR1 &= ~(0xF<<20);// reset sequence length
	if(ONE >= Copy_u8SeqLength)
	{
		CLEARBIT(ADC1->CR1,8);//disable scan mode
	}
	else if(16 >= Copy_u8SeqLength)
	{
		SETBIT(ADC1->CR1,8);//enable scan mode
		ADC1->SQR1 |= (((Copy_u8SeqLength - 1) & 0xF)<<20);//set sequence length
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	if(ADC1_u8EXT_TRIG_SWSTART == Copy_PstrADC1Config->RegularExtTrigger)
	{
		SETBIT(ADC1->CR2,22);// Software start conversion of regular channels
	}


	return Local_enuErrorState;
}


/**********************************************************************************/
ES_t ADC1_enuReadData(u16 *Copy_Pu16Data);
/**********************************************************************************/


ES_t ADC1_enuConfigInjectedChannel(ChannelConfig_t * Copy_PstrChannelConfig)
{
	ES_t Local_enuErrorState =ES_OK;

	if(Copy_PstrChannelConfig)
	{
		if(9 >= Copy_PstrChannelConfig->ChannelID)
		{
			/*for SMPR2: startBit of channel = 3 * ChannelID */
			ADC1->SMPR2 &= ~(0x7 <<(3 * Copy_PstrChannelConfig->ChannelID)); // reset the sampleTime
			ADC1->SMPR2 |= (Copy_PstrChannelConfig->SampleTime <<(3 * Copy_PstrChannelConfig->ChannelID)); // set the new sampleTime
		}
		else if(17 >= Copy_PstrChannelConfig->ChannelID)
		{
			/*for SMPR1: startBit of channel = 3 *( ChannelID - 10)*/
			ADC1->SMPR1 &= ~(0x7 <<(3 * (Copy_PstrChannelConfig->ChannelID - 10 ))); // reset the sampleTime
			ADC1->SMPR1 |= (Copy_PstrChannelConfig->SampleTime <<(3 * (Copy_PstrChannelConfig->ChannelID - 10 ))); // set the new sampleTime
		}
		else
		{
			Local_enuErrorState  = ES_Out_Of_Range;
		}

		if(4 >= Copy_PstrChannelConfig->Rank)
		{
			/*for JSQR: startBit of Rank = 5 * (Rank-1) */
			ADC1->JSQR &= ~(0x1f << ( 5 * (Copy_PstrChannelConfig->Rank - 1)));
			ADC1->JSQR |= (Copy_PstrChannelConfig->ChannelID << ( 5 * (Copy_PstrChannelConfig->Rank - 1)));
		}
		else
		{
			Local_enuErrorState =ES_Out_Of_Range;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULLPOINTER;
	}

	return Local_enuErrorState;
}

ES_t ADC1_enuStartInjectedConversionWithPolling(ADC1_Config_t * Copy_PstrADC1Config, u16 Copy_Pu16Data[4] , u8 Copy_u8SeqLength)
{
	ES_t Local_enuErrorState = ES_OK;
	ADC1->JSQR &= ~(0x3<<20);// reset sequence length
	if(ONE >= Copy_u8SeqLength)
	{
		CLEARBIT(ADC1->CR1,8);//disable scan mode
	}
	else if(4 >= Copy_u8SeqLength)
	{
		SETBIT(ADC1->CR1,8);//enable scan mode
		ADC1->JSQR |= (((Copy_u8SeqLength - 1) & 0x3)<<20);//set sequence length
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	if(ADC1_u8JEXT_TRIG_SWSTART == Copy_PstrADC1Config->InjectedExtTrigger)
	{
		SETBIT(ADC1->CR2,21);// Software start conversion of injected channels
	}

	while(!(GETBIT(ADC1->SR,2)));      // wait JEOC
	switch(Copy_u8SeqLength)
	{
	case 0:
	case 1:
		Copy_Pu16Data[0] = ADC1->JDR1;  // Read injected data register result
		break;
	case 2:
		/* 1st conversion */
		Copy_Pu16Data[0] = ADC1->JDR1;  // Read injected data register result
		/* 2nd conversion */
		Copy_Pu16Data[1] = ADC1->JDR2;  // Read injected data register result
		break;
	case 3:
		/* 1st conversion */
		Copy_Pu16Data[0] = ADC1->JDR1;  // Read injected data register result
		/* 2nd conversion */
		Copy_Pu16Data[1] = ADC1->JDR2;  // Read injected data register result
		/* 3nd conversion */
		Copy_Pu16Data[2] = ADC1->JDR3;  // Read injected data register result
		break;
	case 4:
		/* 1st conversion */
		Copy_Pu16Data[0] = ADC1->JDR1;  // Read injected data register result
		/* 2nd conversion */
		Copy_Pu16Data[1] = ADC1->JDR2;  // Read injected data register result
		/* 3rd conversion */
		Copy_Pu16Data[2] = ADC1->JDR3;  // Read injected data register result
		/* 4th conversion */
		Copy_Pu16Data[3] = ADC1->JDR4;  // Read injected data register result
		break;
	}

	return Local_enuErrorState;
}
ES_t ADC1_enuStartInjectedConversionWithINT(ADC1_Config_t * Copy_PstrADC1Config, u8 Copy_u8SeqLength)
{
	ES_t Local_enuErrorState = ES_OK;

	CLEARBIT(ADC1->SR, 2);   // JEOC = 0, clear injected end of conversion flag
	ADC1->JSQR &= ~(0x3<<20);// reset sequence length
	if(ONE >= Copy_u8SeqLength)
	{
		CLEARBIT(ADC1->CR1,8);//disable scan mode
	}
	else if(4 >= Copy_u8SeqLength)
	{
		SETBIT(ADC1->CR1,8);//enable scan mode
		ADC1->JSQR |= (((Copy_u8SeqLength - 1) & 0x3)<<20);//set sequence length
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	if(ADC1_u8JEXT_TRIG_SWSTART == Copy_PstrADC1Config->InjectedExtTrigger)
	{
		SETBIT(ADC1->CR2,21);// Software start conversion of injected channels
	}


	return Local_enuErrorState;
}
/******************************************************************************************/


ES_t ADC1_enuEnableDisCountMOD(DISC_Mode_t Copy_enuMode,u8 Copy_u8NumOfChannels)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_enuMode)
	{
	case DISC_MODE_REGULAR:
		CLEARBIT(ADC1->CR2,1);// disable continuous mode
		SETBIT(ADC1->CR1,11); // enable  Discontinuous mode on regular channels
		break;
	case DISC_MODE_INJECTED:
		SETBIT(ADC1->CR1,12);// enable  Discontinuous mode on injected channels
		break;
	case DISC_MODE_BOTH:
		CLEARBIT(ADC1->CR2,1);  // disable continuous mode
		SETBIT(ADC1->CR1,11);   // enable  Discontinuous mode on regular channels
		SETBIT(ADC1->CR1,12);   // enable  Discontinuous mode on injected channels
		break;
	default:
		Local_enuErrorState = ES_Out_Of_Range;
	}
	if(8 >= Copy_u8NumOfChannels && 1 <= Copy_u8NumOfChannels)
	{
		ADC1->CR1 &= ~(0x7<<13);// reset Discontinuous mode channel count
		ADC1->CR1 |= (((Copy_u8NumOfChannels - 1) & 0x7) << 13);// reset Discontinuous mode channel count
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}


ES_t ADC1_enuDisableDisCountMOD( DISC_Mode_t Copy_enuMode)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_enuMode)
	{
	case DISC_MODE_REGULAR:
		CLEARBIT(ADC1->CR1,11); // disable  Discontinuous mode on regular channels
		break;
	case DISC_MODE_INJECTED:
		CLEARBIT(ADC1->CR1,12);// disable  Discontinuous mode on injected channels
		break;
	case DISC_MODE_BOTH:
		CLEARBIT(ADC1->CR1,11);   // disable  Discontinuous mode on regular channels
		CLEARBIT(ADC1->CR1,12);   // disable  Discontinuous mode on injected channels
		break;
	default:
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;
}




/******************************************************************************************/
ES_t ADC1_enuConfigAnalogWatchdog(f32 Copy_f32HighThreshold, f32 Copy_f32LowThreshold, ChannelID_t Copy_u8channelID,AWD_Mode_t Copy_enuMode)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_f32HighThreshold > Copy_f32LowThreshold && ADC_u8Vref >= Copy_f32HighThreshold && 0.0f <= Copy_f32LowThreshold && ADC1_u8Channel18>= Copy_u8channelID)
	{
		ADC1->CR1 &= ~(0x1F<<0);
		SETBIT(ADC1->CR1,9);

		ADC1->CR1 &= ~(0x3<<22);// disable watch dog for (injected & regular) channels

		switch(Copy_enuMode)
		{
		case AWD_MODE_REGULAR:
			SETBIT(ADC1->CR1,23);// enable watch dog for regular channels
			break;
		case AWD_MODE_INJECTED:
			SETBIT(ADC1->CR1,22);// enable watch dog for injected channels
			break;
		case AWD_MODE_BOTH:
			SETBIT(ADC1->CR1,22);// enable watch dog for injected channels
			SETBIT(ADC1->CR1,23);// enable watch dog for regular channels
			break;
		default:
			Local_enuErrorState = ES_Out_Of_Range;
		}


		ADC1->HTR = (u16)((4095 * Copy_f32HighThreshold   )  / ADC_u8Vref); // set high limit of channel for WatchDog
		ADC1->LTR = (u16)((4095 * Copy_f32LowThreshold    )  / ADC_u8Vref);  // set low limit of channel for WatchDog
		ADC1->CR1 |= (Copy_u8channelID<<0); // select channel
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}
	return Local_enuErrorState;
}
/**********************************************************************************/



ES_t ADC1_enuEnableINT(INTSource_t Copy_u8interruptSource)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_u8interruptSource)
	{
	case ADC1_u8InjectedEndOfConversion:
		SETBIT(ADC1->CR1,7); // enable Interrupt for injected channels
		break;
	case ADC1_u8RegularEndOfConversion:
		SETBIT(ADC1->CR1,5);// enable Interrupt for regular channels
		break;
	case ADC1_u8AnalogWatchdog:
		SETBIT(ADC1->CR1,6);// enable Analog watchdog interrupt
		break;
	default:
		Local_enuErrorState = ES_NOK;
	}
	return Local_enuErrorState;
}
ES_t ADC1_enuDisableINT(INTSource_t Copy_u8interruptSource)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_u8interruptSource)
	{
	case ADC1_u8InjectedEndOfConversion:
		CLEARBIT(ADC1->CR1,7); // disable Interrupt for injected channels
		break;
	case ADC1_u8RegularEndOfConversion:
		CLEARBIT(ADC1->CR1,5);// disable Interrupt for regular channels
		break;
	case ADC1_u8AnalogWatchdog:
		CLEARBIT(ADC1->CR1,6);// disable Analog watchdog interrupt
		break;
	default:
		Local_enuErrorState = ES_NOK;
	}
	return Local_enuErrorState;
}

/**********************************************************************************/
ES_t ADC1_enuEnableDMA(void)
{
	ES_t Local_enuErrorState = ES_OK;
	SETBIT(ADC1->CR2,8);
	return Local_enuErrorState;
}

ES_t ADC1_enuDisableDMA(void)
{
	ES_t Local_enuErrorState = ES_OK;
	CLEARBIT(ADC1->CR2,8);
	return Local_enuErrorState;
}
/**********************************************************************************/


ES_t ADC1_enuSetCallBackFun(ADC1_CbId_t Copy_enuCallBackID,void (*Copy_P2Fun)(void))
{

	ES_t Local_enuErrorState = ES_OK;

	if(ADC1_CB_COUNT > Copy_enuCallBackID)
	{
		ADC1_AVidPtr2Fun[Copy_enuCallBackID] = Copy_P2Fun;
	}
	else
	{
		Local_enuErrorState = ES_Out_Of_Range;
	}

	return Local_enuErrorState;

}

void ADC1_2_IRQHandler(void)
{
	if(GETBIT(ADC1->SR,0))// check Analog watchdog flag
	{
		CLEARBIT(ADC1->SR,0);// clear Analog watchdog flag
		if(ADC1_AVidPtr2Fun[ADC1_CB_AWD])
		{
			ADC1_AVidPtr2Fun[ADC1_CB_AWD]();
		}
		else
		{
			/* Do Nothing*/
		}
	}

	if(GETBIT(ADC1->SR,1))// check End of conversion flag
	{
		CLEARBIT(ADC1->SR,1);// clear End of conversion flag
		if(ADC1_AVidPtr2Fun[ADC1_CB_EOC])
		{
			ADC1_AVidPtr2Fun[ADC1_CB_EOC]();
		}
		else
		{
			/* Do Nothing*/
		}
	}
	if(GETBIT(ADC1->SR,2))// check  Injected channel end of conversion flag
	{
		CLEARBIT(ADC1->SR,2);// clear  Injected channel end of conversion flag
		if(ADC1_AVidPtr2Fun[ADC1_CB_JEOC])
		{
			ADC1_AVidPtr2Fun[ADC1_CB_JEOC]();
		}
		else
		{
			/* Do Nothing*/
		}
	}
	if(GETBIT(ADC1->SR,3))// check  Injected channel Start flag
	{
		CLEARBIT(ADC1->SR,3);// clear  Injected channel Start flag
		if(ADC1_AVidPtr2Fun[ADC1_CB_JSTRT])
		{
			ADC1_AVidPtr2Fun[ADC1_CB_JSTRT]();
		}
		else
		{
			/* Do Nothing*/
		}

	}
	if(GETBIT(ADC1->SR,4))// check Regular channel Start flag
	{
		CLEARBIT(ADC1->SR,4);// clear Regular channel Start flag
		if(ADC1_AVidPtr2Fun[ADC1_CB_STRT])
		{
			ADC1_AVidPtr2Fun[ADC1_CB_STRT]();
		}
		else
		{
			/* Do Nothing*/
		}

	}
}
