/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 17/8/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : ADC1          ******************/
/*************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include"LIB/StdTypes.h"
#include"LIB/BitMath.h"
#include"LIB/errorStatuse.h"

typedef enum
{
	ADC1_u8Independent_mode,
	ADC1_u8CombinedRegularSimultaneous_InjectedSimultaneousMode,
	ADC1_u8CombinedRegularSimultaneous_AlternateTriggerMode,
	ADC1_u8CombinedInjectedSimultaneous_FastInterleavedMode,
	ADC1_u8CombinedInjectedSimultaneous_SlowInterleavedMode,
	ADC1_u8InjectedSimultaneousModeOnly,
	ADC1_u8RegularSimultaneousModeOnly,
	ADC1_u8FastInterleavedModeOnly,
	ADC1_u8SlowInterleavedModeOnly,
	ADC1_u8AlternateTriggerModeOnly
}DUALMOD_t;

typedef enum {
    AWD_MODE_REGULAR,
    AWD_MODE_INJECTED,
    AWD_MODE_BOTH
} AWD_Mode_t;
typedef enum {
	DISC_MODE_REGULAR,
	DISC_MODE_INJECTED,
	DISC_MODE_BOTH
} DISC_Mode_t;

typedef enum
{
	ADC1_u8SingleConversionMode,
	ADC1_u8ContinuousMode
}SingleContinuousConv_t;

typedef enum
{
	ADC1_u8RIGHT,
	ADC1_u8LEFT
}DataAlign_t;

typedef enum
{
	ADC1_u8ScanDisable,
	ADC1_u8ScanEnable
}ScanMode_t;



typedef enum
{
	ADC1_u8EXT_TRIG_TIM1CC1  ,
	ADC1_u8EXT_TRIG_TIM1CC2  ,
	ADC1_u8EXT_TRIG_TIM1CC3  ,
	ADC1_u8EXT_TRIG_TIM2CC2  ,
	ADC1_u8EXT_TRIG_TIM3TRGO ,
	ADC1_u8EXT_TRIG_TIM4CC4  ,
	ADC1_u8EXT_TRIG_EXTI11   ,
	ADC1_u8EXT_TRIG_SWSTART  //  Regular
} RegularExtTrigger_t;

typedef enum
{
	ADC1_u8JEXT_TRIG_TIM1TRGO,
	ADC1_u8JEXT_TRIG_TIM1CC4 ,
	ADC1_u8JEXT_TRIG_TIM2CC1 ,
	ADC1_u8JEXT_TRIG_TIM2TRGO,
	ADC1_u8JEXT_TRIG_TIM3CC2 ,
	ADC1_u8JEXT_TRIG_TIM3CC4 ,
	ADC1_u8JEXT_TRIG_TIM4TRGO,
	ADC1_u8JEXT_TRIG_SWSTART // Injected
} InjectedExtTrigger_t;

enum
{
	ADC1_u8Disable,
	ADC1_u8Enable,
};


typedef struct
{
	DUALMOD_t             DualMode;
	SingleContinuousConv_t          continuousConv;         // continuous or single
	ScanMode_t             Scan_SinglChannel;				// enable scan_disabe singleChannel or disable scan_enable singleChannel
	DataAlign_t           dataAlign;                        // RIGHT / LEFT
    u8 			          RegularExtriggerConvState;		// ADC1_u8Disable or ADC1_u8Enable
    RegularExtTrigger_t   RegularExtTrigger;                // TIMER / EXTI / SWSTART

    u8 			          InjectedExtriggerConvState;       // ADC1_u8Disable or ADC1_u8Enable
    InjectedExtTrigger_t  InjectedExtTrigger;               // TIMER / EXTI / SWSTART
} ADC1_Config_t;


typedef enum
{
	ADC1_u8Channel0,
	ADC1_u8Channel1,
	ADC1_u8Channel2,
	ADC1_u8Channel3,
	ADC1_u8Channel4,
	ADC1_u8Channel5,
	ADC1_u8Channel6,
	ADC1_u8Channel7,
	ADC1_u8Channel8,
	ADC1_u8Channel9,
	ADC1_u8Channel10,
	ADC1_u8Channel11,
	ADC1_u8Channel12,
	ADC1_u8Channel13,
	ADC1_u8Channel14,
	ADC1_u8Channel15,
	ADC1_u8Channel16,
	ADC1_u8Channel17,
	ADC1_u8Channel18

}ChannelID_t;

typedef enum
{
	ADC1_1_5Cycle,
	ADC1_7_5Cycle,
	ADC1_13_5Cycle,
	ADC1_28_5Cycle,
	ADC1_41_5Cycle,
	ADC1_55_5Cycle,
	ADC1_71_5Cycle,
	ADC1_239_5Cycle,

}SampleTime_t;

typedef enum
{
	ADC_u8_1stConversion = ONE,
	ADC_u8_2stConversion      ,
	ADC_u8_3stConversion      ,
	ADC_u8_4stConversion      ,
	ADC_u8_5stConversion      ,
	ADC_u8_6stConversion      ,
	ADC_u8_7stConversion      ,
	ADC_u8_8stConversion      ,
	ADC_u8_9stConversion      ,
	ADC_u8_10stConversion     ,
	ADC_u8_11stConversion     ,
	ADC_u8_12stConversion     ,
	ADC_u8_13stConversion     ,
	ADC_u8_14stConversion     ,
	ADC_u8_15stConversion     ,
	ADC_u8_16stConversion

}Rank_t;

typedef struct
{
	ChannelID_t  ChannelID;
	SampleTime_t SampleTime;
	Rank_t       Rank;
}ChannelConfig_t;

typedef enum
{
	ADC1_u8InjectedEndOfConversion,
	ADC1_u8RegularEndOfConversion,
	ADC1_u8AnalogWatchdog
}INTSource_t;

typedef enum
{
	 ADC1_CB_AWD  ,      // Analog Watchdog interrupt callback
	 ADC1_CB_EOC  ,      // End of Conversion callback
     ADC1_CB_JEOC ,      // End of Injected Conversion callback
     ADC1_CB_JSTRT,      // Injected group start callback
	 ADC1_CB_STRT ,      // Regular group start callback
	 ADC1_CB_COUNT       // Total count of callbacks
}ADC1_CbId_t;
ES_t ADC1_enuInit(ADC1_Config_t * Copy_PstrADC1Config);

ES_t ADC1_enuConfigRegularChannel(ChannelConfig_t * Copy_PstrChannelConfig);
ES_t ADC1_enuStartRegularConversionWithPolling(ADC1_Config_t * Copy_PstrADC1Config, u16 Copy_Pu16Data[16] , u8 Copy_u8SeqLength);
ES_t ADC1_enuStartRegularConversionWithINT(ADC1_Config_t * Copy_PstrADC1Config, u8 Copy_u8SeqLength);

ES_t ADC1_enuReadDataOfRegular(u16 *Copy_Pu16Data);

ES_t ADC1_enuConfigInjectedChannel(ChannelConfig_t * Copy_PstrChannelConfig);

ES_t ADC1_enuStartInjectedConversionWithPolling(ADC1_Config_t * Copy_PstrADC1Config, u16 Copy_Pu16Data[16] , u8 Copy_u8SeqLength);
ES_t ADC1_enuStartInjectedConversionWithINT(ADC1_Config_t * Copy_PstrADC1Config, u8 Copy_u8SeqLength);

ES_t ADC1_enuEnableDisCountMOD(DISC_Mode_t Copy_enuMode,u8 Copy_u8NumOfChannels);
ES_t ADC1_enuDisableDisCountMOD( DISC_Mode_t Copy_enuMode);

ES_t ADC1_enuConfigAnalogWatchdog(f32 Copy_f32HighThreshold, f32 Copy_f32LowThreshold, ChannelID_t Copy_u8channelID,AWD_Mode_t Copy_enuMode);
ES_t ADC1_enuEnableINT(INTSource_t Copy_u8interruptSource);
ES_t ADC1_enuDisableINT( INTSource_t Copy_u8interruptSource);

ES_t ADC1_enuEnableDMA(void);
ES_t ADC1_enuDisableDMA(void);


ES_t ADC1_enuSetCallBackFun(ADC1_CbId_t Copy_enuCallBackID,void (*Copy_P2Fun)(void));




#endif /* ADC_INTERFACE_H_ */
