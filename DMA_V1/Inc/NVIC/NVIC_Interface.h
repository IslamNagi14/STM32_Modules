/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 30/6/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : NVIC         ******************/
/*************************************************************/
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include"StdTypes.h"
#include"errorStatuse.h"
#include"BitMath.h"

ES_t NVIC_enuEnableINT       (u8 Copy_u8PrephiralID);
ES_t NVIC_enuDisableINT      (u8 Copy_u8PrephiralID);


ES_t NVIC_enuSetPendingINT   (u8 Copy_u8PrephiralID);
ES_t NVIC_enuClearPendingINT (u8 Copy_u8PrephiralID);


ES_t NVIC_enuGetINTStatues(u8 Copy_u8PrephiralID , u8* Copy_Pu8INTStatues);


ES_t NVIC_enuSetGroupPriority  (u8 Copy_u8PrephiralID , u8 Copy_u8GroupPriority);



/******************************    Prephiral's IDs              *******************************/


/******************************          [0]         *******************************/

#define NVIC_u8_WWDG              0
#define NVIC_u8_PVD                    1
#define NVIC_u8_TAMPER                 2
#define NVIC_u8_RTC                    3
#define NVIC_u8_FLASH                  4
#define NVIC_u8_NVIC_RCC               5
#define NVIC_u8_EXTI0                  6
#define NVIC_u8_EXTI1                  7
#define NVIC_u8_EXTI2                  8
#define NVIC_u8_EXTI3                  9
#define NVIC_u8_EXTI4                  10
#define NVIC_u8_DMA1_Channel1          11
#define NVIC_u8_DMA1_Channel2          12
#define NVIC_u8_DMA1_Channel3          13
#define NVIC_u8_DMA1_Channel4          14
#define NVIC_u8_DMA1_Channel5          15
#define NVIC_u8_DMA1_Channel6          16
#define NVIC_u8_DMA1_Channel7          17
#define NVIC_u8_ADC1_2                 18
#define NVIC_u8_USB_HP_CAN_TX          19
#define NVIC_u8_USB_LP_CAN_RX0         20
#define NVIC_u8_CAN_RX1                21
#define NVIC_u8_CAN_SCE                22
#define NVIC_u8_EXTI9_5                23
#define NVIC_u8_TIM1_BRK               24
#define NVIC_u8_TIM1_UP                25
#define NVIC_u8_TIM1_TRG_COM           26
#define NVIC_u8_TIM1_CC                27
#define NVIC_u8_TIM2                   28
#define NVIC_u8_TIM3                   29
#define NVIC_u8_TIM4                   30
#define NVIC_u8_I2C1_EV                31

/**********************************************************************************/


/******************************          [1]         *******************************/

#define NVIC_u8_I2C1_ER               (0  + 32)
#define NVIC_u8_I2C2_EV               (1  + 32)
#define NVIC_u8_I2C2_ER               (2  + 32)
#define NVIC_u8_SPI1                  (3  + 32)
#define NVIC_u8_SPI2                  (4  + 32)
#define NVIC_u8_USART1                (5  + 32)
#define NVIC_u8_USART2                (6  + 32)
#define NVIC_u8_USART3                (7  + 32)
#define NVIC_u8_EXTI15_10             (8  + 32)
#define NVIC_u8_RTCAlarm              (9  + 32)
#define NVIC_u8_USBWakeup             (10 + 32)
#define NVIC_u8_TIM8_BRK              (11 + 32)////////////
#define NVIC_u8_TIM8_UP               (12 + 32)
#define NVIC_u8_TIM8_TRG_COM          (13 + 32)
#define NVIC_u8_TIM8_CC               (14 + 32)
#define NVIC_u8_ADC3                  (15 + 32)
#define NVIC_u8_FSMC                  (16 + 32)
#define NVIC_u8_SDIO                  (17 + 32)
#define NVIC_u8_TIM5                  (18 + 32)
#define NVIC_u8_SPI3                  (19 + 32)
#define NVIC_u8_UART4                 (20 + 32)
#define NVIC_u8_UART5                 (21 + 32)
#define NVIC_u8_TIM6                  (22 + 32)
#define NVIC_u8_TIM7                  (23 + 32)
#define NVIC_u8_DMA2_Channel1         (24 + 32)
#define NVIC_u8_DMA2_Channel2         (25 + 32)
#define NVIC_u8_DMA2_Channel3         (26 + 32)
#define NVIC_u8_DMA2_Channel4_5       (27 + 32)


/**********************************************************************************/


/******************************          [2]         *******************************/

#define NVIC_u8_CAN2_RX0            (0  + 64)
#define NVIC_u8_CAN2_RX1            (1  + 64)
#define NVIC_u8_CAN2_SCE            (2  + 64)
#define NVIC_u8_OTG_FS              (3  + 64)


/**********************************************************************************/




/*********************************************************************************************/

#endif /* NVIC_INTERFACE_H_ */
