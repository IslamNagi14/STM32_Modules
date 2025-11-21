/*************************************************************/
/********************Name    : Islam Nagi	******************/
/********************Date    : 15/4/2025    ******************/
/********************Version : 1.0          ******************/
/********************SWC     : RCC          ******************/
/*************************************************************/

#ifndef __RCC_CONFIG_H__
#define __RCC_CONFIG_H__
#include "RCC_Int.h"
/*
 * RCC_U8_CLK_SYS: 1-RCC_u8HIGH_SPEED_EXTERNAL_CLOCK
 * 				   2-RCC_u8HIGH_SPEED_INTERNAL_CLOCK
 * 				   3-RCC_u8PHASE_LOCKED_LOOP_CLOCK
 */
#define RCC_U8_CLK_SYS          RCC_u8HIGH_SPEED_INTERNAL_CLOCK

/*
 * if you select "RCC_u8HIGH_SPEED_EXTERNAL_CLOCK"
 * you must select type of clock source : 1-RCC_u8_CERAMIC_CRYSTAL
 * 										  2-RCC_u8_RC
 * */
#define EXT_SOURCE_TYPE			RCC_u8_CERAMIC_CRYSTAL


/*
 * if you select "RCC_u8PHASE_LOCKED_LOOP_CLOC"
 * you must select PLL_ENTRY_CLK 1-RCC_u8HIGH_SPEED_EXTERNAL_CLOCK ("input = HSE/1 or HSE/2")
 * 								 2-RCC_u8HIGH_SPEED_INTERNAL_CLOCK ("input = HSI/2")
 *
 * then if you select RCC_u8HIGH_SPEED_EXTERNAL_CLOCK
 * you must select the HSE_DIVIDED_FACTOR : 1- 1
 * 										    2- 2
 *
 * after that select the PLL_MUL_FACTOR : Number from 2 to 16 (The PLL output frequency must not exceed 72MHz)
 * */

#define PLL_ENTRY_CLK		RCC_u8HIGH_SPEED_EXTERNAL_CLOCK
#define	HSE_DIVIDED_FACTOR		1
#define PLL_MUL_FACTOR			2
#endif
