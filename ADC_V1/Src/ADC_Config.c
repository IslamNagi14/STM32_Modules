/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 17/8/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : ADC1          ******************/
/*************************************************************/

#include"../Inc/ADC/ADC_Interface.h"
#include"../Inc/ADC/ADC_Config.h"


ADC1_Config_t ADC1_strConfig1 =
{
	.DualMode = ADC1_u8Independent_mode   			 ,
	.continuousConv = ADC1_u8SingleConversionMode 	 ,
	.Scan_SinglChannel = ADC1_u8ScanEnable			 ,
	.dataAlign = ADC1_u8RIGHT 						 ,
	.RegularExtriggerConvState = ADC1_u8Enable		 ,
	.RegularExtTrigger = ADC1_u8EXT_TRIG_SWSTART	 ,
	.InjectedExtriggerConvState = ADC1_u8Disable	 ,
	.InjectedExtTrigger = ADC1_u8JEXT_TRIG_SWSTART
};


