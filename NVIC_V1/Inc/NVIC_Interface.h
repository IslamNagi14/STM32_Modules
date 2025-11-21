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

#define NVIC_WWDG              0
#define PVD                    1
#define TAMPER                 2
#define RTC                    3
#define FLASH                  4
#define NVIC_RCC               5
#define EXTI0                  6
#define EXTI1                  7
#define EXTI2                  8
#define EXTI3                  9
#define EXTI4                  10
#define DMA1_Channel1          11
#define DMA1_Channel2          12
#define DMA1_Channel3          13
#define DMA1_Channel4          14
#define DMA1_Channel5          15
#define DMA1_Channel6          16
#define DMA1_Channel7          17
#define ADC1_2                 18
#define USB_HP_CAN_TX          19
#define USB_LP_CAN_RX0         20
#define CAN_RX1                21
#define CAN_SCE                22
#define EXTI9_5                23
#define TIM1_BRK               24
#define TIM1_UP                25
#define TIM1_TRG_COM           26
#define TIM1_CC                27
#define TIM2                   28
#define TIM3                   29
#define TIM4                   30
#define I2C1_EV                31

/**********************************************************************************/


/******************************          [1]         *******************************/

#define I2C1_ER               (0  + 32)
#define I2C2_EV               (1  + 32)
#define I2C2_ER               (2  + 32)
#define SPI1                  (3  + 32)
#define SPI2                  (4  + 32)
#define USART1                (5  + 32)
#define USART2                (6  + 32)
#define USART3                (7  + 32)
#define EXTI15_10             (8  + 32)
#define RTCAlarm              (9  + 32)
#define USBWakeup             (10 + 32)
#define TIM8_BRK              (11 + 32)
#define TIM8_UP               (12 + 32)
#define TIM8_TRG_COM          (13 + 32)
#define TIM8_CC               (14 + 32)
#define ADC3                  (15 + 32)
#define FSMC                  (16 + 32)
#define SDIO                  (17 + 32)
#define TIM5                  (18 + 32)
#define SPI3                  (19 + 32)
#define UART4                 (20 + 32)
#define UART5                 (21 + 32)
#define TIM6                  (22 + 32)
#define TIM7                  (23 + 32)
#define DMA2_Channel1         (24 + 32)
#define DMA2_Channel2         (25 + 32)
#define DMA2_Channel3         (26 + 32)
#define DMA2_Channel4_5       (27 + 32)


/**********************************************************************************/


/******************************          [2]         *******************************/

//#define CAN2_RX0            (0  + 64)
//#define CAN2_RX1            (1  + 64)
//#define CAN2_SCE            (2  + 64)
//#define OTG_FS              (3  + 64)


/**********************************************************************************/




/*********************************************************************************************/

#endif /* NVIC_INTERFACE_H_ */
