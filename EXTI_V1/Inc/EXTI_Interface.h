/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 1/7/2025     ******************/
/********************Version : 1.0          ******************/
/********************SWC     : EXTI         ******************/
/*************************************************************/


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#include"StdTypes.h"
#include"BitMath.h"
#include"errorStatuse.h"






/********************         INT States     ***************************/


typedef enum
{
	EXTI_u8_Disable,
	EXTI_u8_Enable,

}EXTI_States;
/***********************************************************************/

/********************         EdGes LEVELS    ***************************/
typedef enum
{
	EXTI_u8_Rising_Edge = 54,
	EXTI_u8_Falling_Edge,
	EXTI_u8_Rising_Falling_Edge

}EXTI_Edges_Levels;



/***********************************************************************/


/********************         EXTIs          ***************************/

typedef enum
{
	EXTI_u8_LINE0,
	EXTI_u8_LINE1,
	EXTI_u8_LINE2,
	EXTI_u8_LINE3,
	EXTI_u8_LINE4,
	EXTI_u8_LINE5_9,
	EXTI_u8_LINE10_15


}EXTIs;

/***********************************************************************/


/********************         EXTIs' Characters          ***************************/

typedef struct
{
	volatile EXTIs EXTI_ID;

	volatile EXTI_States EXTI_State;

	volatile EXTI_Edges_Levels EXTI_EdgeType;
}EXTI_DefEXTI_t;

/***********************************************************************/



/**********************************************functions' prototypes ********************************************************************/

ES_t EXTI_enuSetINTStatus(const EXTI_DefEXTI_t* Copy_pu8EINT);//set edge level and set the EXTI[enabled - Not masked] or [disabled - masked]

ES_t EXTI_enuEnableINT(EXTIs Copy_u8INT_ID);//Enable EXTIx

ES_t EXTI_enuDisableINT(EXTIs Copy_u8INT_ID);//Disable EXTIx

ES_t EXTI_enuClearINTPending(EXTIs Copy_u8INT_ID);//clear pending

ES_t EXTI_enuIsINTActive(EXTIs Copy_u8INT_ID , u8* Copy_pu8EXTI_Status);

ES_t EXTI_enuGenerate_SW_INT(EXTIs Copy_u8INT_ID);

ES_t EXTI_enuSetCallBackFun(EXTIs Copy_u8INT_ID , void (*Copy_P2Fun)(void));


#endif /* EXTI_INTERFACE_H_ */
