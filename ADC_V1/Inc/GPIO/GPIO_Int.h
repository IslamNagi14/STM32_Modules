/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 26/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : GPIO          ******************/
/*************************************************************/

#ifndef __GPIO_INT_H__
#define __GPIO_INT_H__

#include "LIB/StdTypes.h"
#include "LIB/errorStatuse.h"

typedef enum
{
	GPIO_u8PIN0,
	GPIO_u8PIN1,
	GPIO_u8PIN2,
	GPIO_u8PIN3,
	GPIO_u8PIN4,
	GPIO_u8PIN5,
	GPIO_u8PIN6,
	GPIO_u8PIN7,
	GPIO_u8PIN8,
	GPIO_u8PIN9,
	GPIO_u8PIN10,
	GPIO_u8PIN11,
	GPIO_u8PIN12,
	GPIO_u8PIN13,
	GPIO_u8PIN14,
	GPIO_u8PIN15
}GPIOxPINS_t;

typedef enum
{
	GPIO_u8GPIO_A,
	GPIO_u8GPIO_B,
	GPIO_u8GPIO_C

}GPIOxPORTS_t;

typedef enum 
{
	/*                  Output Modes               */
	/*				10MHz             */
	GPIO_u8Output10MHzPushPull  = 0b0001,
	GPIO_u8Output10MHzOpenDrain = 0b0101,
	APIO_u8Output10MHzPushPull  = 0b1001,
	APIO_u8Output10MHzOpenDrain = 0b1101,
	/*				2MHz             */
	GPIO_u8Output2MHzPushPull   = 0b0010,
	GPIO_u8Output2MHzOpenDrain  = 0b0110,
	APIO_u8Output2MHzPushPull   = 0b1010,
	APIO_u8Output2MHzOpenDrain  = 0b1110,
	/*				    50MHz            */
	GPIO_u8Output50MHzPushPull  = 0b0011,
	GPIO_u8Output50MHzOpenDrain = 0b0111,
	APIO_u8Output50MHPushPull   = 0b1011,
	APIO_u8Output50MHOpenDrain  = 0b1111,
	/***********************************************/

	/*            Input Modes                      */
	GPIO_u8InputAnalog          = 0b0000,
	GPIO_u8InputFloating        = 0b0100,
	GPIO_u8InputPullDown        = 0b1000, //before doing any thing check the bit0 if 1 it is PullUp"clear bit0 and set ODRbit of the received pin and if else the bit0 is 0 it is pulldown and put 0 in ODRbit of the received pin after all that put the value of CNF[1:0] and MODE[1:0]"
	GPIO_u8InputPullUp          = 0b1001  //before doing any thing check the bit0 if 1 it is PullUp"clear bit0 and set ODRbit of the received pin and if else the bit0 is 0 it is pulldown and put 0 in ODRbit of the received pin after all that put the value of CNF[1:0] and MODE[1:0]"
	/***********************************************/

}GPIOx_PinMode_t;
typedef enum
{
	GPIO_u8LOW 	,
	GPIO_u8HIGH	,
	GPIO_u8FLOAT
}GPIOx_Val_t;
typedef struct
{
	GPIOxPORTS_t		PortId		;
	GPIOxPINS_t			PinId 		;
	GPIOx_PinMode_t 	PinMode     ;
}GPIO_PinCongig_t;



ES_t GPIO_enuSetPinMode				(const GPIO_PinCongig_t * Copy_PstrPinConfig);
ES_t GPIO_enuSetPinVal				    (const GPIO_PinCongig_t * Copy_PstrPinConfig,GPIOx_Val_t Copy_enuPinVal);
ES_t GPIO_enuGetPinVal				    (const GPIO_PinCongig_t * Copy_PstrPinConfig,u8 *Copy_pu8PinVal);
ES_t GPIO_enuTogPinVal		            (const GPIO_PinCongig_t * Copy_PstrPinConfig);
#endif
