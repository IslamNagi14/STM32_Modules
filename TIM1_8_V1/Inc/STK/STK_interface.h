/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 10/5/2025    ******************/
/********************Version    : 1.0       ******************/
/********************SWC    : STK   ******************/
/*************************************************************/

#ifndef  __STK_INTERFACE__H__
#define  __STK_INTERFACE__H__

#include"LIB/StdTypes.h"
#include"LIB/BitMath.h"
#include"LIB/errorStatuse.h"

void STK_vidInitSTK                (void);//set prescaleing + disable STK
/*                Synch function                  */
ES_t STK_enuSyncDelay               (u32 Copy_u32DelyedTime);
/*                ASynch function                  */
ES_t STK_enuASyncDelaySingleShot    (u32 Copy_u32DelyedTime,void (*Copy_pf)(void));
ES_t STK_enuASyncDelayMultiShot     (u32 Copy_u32DelyedTime,void (*Copy_pf)(void));
/*------------------------------------------------------*/

ES_t STK_enuStopTimer               (void);
ES_t STK_enuGetElapsedTime          (u32 *Copy_Pu32ElapsedTime);
ES_t STK_enuGetRemainingTime        (u32 *Copy_Pu32RemainingTime);




#endif
