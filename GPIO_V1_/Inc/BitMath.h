/*
 * BitMath.h
 *
 *  Created on: Apr 15, 2025
 *      Author: Islam Nagi
 */

#ifndef BITMATH_H_
#define BITMATH_H_

#define ONE						1
#define GETBIT(Variable,Bnum)		((Variable>>Bnum)&ONE)
#define SETBIT(Variable,Bnum)		Variable|=(ONE<<Bnum)
#define CLEARBIT(Variable,Bnum)		Variable&=~(ONE<<Bnum)
#define TOGGLEBIT(Variable,Bnum)	Variable^=(ONE<<Bnum)

#endif /* BITMATH_H_ */
