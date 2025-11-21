/**************************************************************/
/********************Name    : Islam Nagi	*******************/
/********************Date    : 22/8/2025    *******************/
/********************Version    : 1.0       *******************/
/********************SWC    : Timer(1 & 8)   ******************/
/**************************************************************/

#ifndef TIM18_TIM18_INTERFACE_H_
#define TIM18_TIM18_INTERFACE_H_

#include"LIB/StdTypes.h"
#include"LIB/errorStatuse.h"

/******** Timer IDs ********/
typedef enum {
    TIM1_ID = 1,
    TIM2_ID,
    TIM3_ID,
    TIM4_ID,
    TIM5_ID,
    TIM6_ID,
    TIM7_ID,
    TIM8_ID
} TIM_Id_t;


/******** PWM Alignment Modes ********/
typedef enum {
    TIM_PWM_EDGE_ALIGNED = 0,
    TIM_PWM_CENTER_ALIGNED
} TIM_PWM_Alignment_t;


/******** PWM Channels ********/
typedef enum {
    TIM_CHANNEL_1 = 1,
    TIM_CHANNEL_2,
    TIM_CHANNEL_3,
    TIM_CHANNEL_4
} TIM_Channel_t;


/******** Input Capture Edge Selection ********/
typedef enum {
    TIM_IC_RISING_EDGE = 0,
    TIM_IC_FALLING_EDGE,
    TIM_IC_BOTH_EDGES
} TIM_IC_Edge_t;
/*********************************interrupts*********************************/
typedef enum
{
    TIM_INT_UIE  = 0,   // Update interrupt enable (UIF flag, DIER bit 0)

    TIM_INT_CC1IE = 1,  // Capture/Compare 1 interrupt enable (CC1IF, DIER bit 1)
    TIM_INT_CC2IE = 2,  // Capture/Compare 2 interrupt enable (CC2IF, DIER bit 2)
    TIM_INT_CC3IE = 3,  // Capture/Compare 3 interrupt enable (CC3IF, DIER bit 3)
    TIM_INT_CC4IE = 4,  // Capture/Compare 4 interrupt enable (CC4IF, DIER bit 4)

    // Aliases for CTC mode (Compare Match)
    TIM_INT_CTC1 = TIM_INT_CC1IE,
    TIM_INT_CTC2 = TIM_INT_CC2IE,
    TIM_INT_CTC3 = TIM_INT_CC3IE,
    TIM_INT_CTC4 = TIM_INT_CC4IE

} TIM_Interrupt_t;
/***********************************************************************************/


/****************** Basic Delay ******************/
ES_t TIM_enuDelaySync_ms(TIM_Id_t Copy_enuTimID, u32 Copy_u32Delay_ms);
ES_t TIM_enuDelayAsync_ms(TIM_Id_t Copy_enuTimID, u32 Copy_u32Delay_ms);

/****************** CTC Mode ******************/
ES_t TIM_enuEnableCTC(TIM_Id_t tim_id, TIM_Channel_t channel, u16 compare_value);
ES_t TIM_enuDisableCTC(TIM_Id_t tim_id, TIM_Channel_t channel);


/****************** PWM Generation ******************/
ES_t TIM_enuPWM_Init(TIM_Id_t tim_id, TIM_Channel_t channel, u32 freq_hz, TIM_PWM_Alignment_t alignment_mode);
ES_t TIM_enuPWM_SetDuty(TIM_Id_t tim_id, TIM_Channel_t channel, float duty_percent);
ES_t TIM_enuPWM_Start(TIM_Id_t tim_id, TIM_Channel_t channel);
ES_t TIM_enuPWM_Stop(TIM_Id_t tim_id, TIM_Channel_t channel);


/****************** Input Capture ******************/
ES_t TIM_enuIC_Init(TIM_Id_t tim_id, TIM_Channel_t channel, TIM_IC_Edge_t edge, u8 prescaler);
ES_t TIM_enuIC_GetValue(TIM_Id_t tim_id, TIM_Channel_t channel,u16 * Copy_Pu16Val);
ES_t TIM_enuIC_EnableInterrupt(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel);
ES_t TIM_enuIC_DisableInterrupt(TIM_Id_t Copy_enuTimID, TIM_Channel_t Copy_enuChannel);

/***********************************************************************************/

ES_t TIM_enuCallBack(TIM_Id_t Copy_enuTimID,TIM_Interrupt_t Copy_enuInterruptID, void (*Copy_PvidFun)(void) );

#endif /* TIM18_TIM18_INTERFACE_H_ */
