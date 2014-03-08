/*
Simple Software Rasterising Engine

Copyright (c) 2014 Neil Richardson (neilogd)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef __SSRE_FIXED_H__
#define __SSRE_FIXED_H__

#include "SSRE_Types.h"

/**
 * Fixed point type.
 */
typedef s32 SSRE_Fixed_t;

/**
 * Fixed point precision level.
 */
#define SSRE_FIXED_PRECISION			( 16 )
#define SSRE_FIXED_DOUBLE_PRECISION		( SSRE_FIXED_PRECISION << 1 )
#define SSRE_FIXED_HALF_PRECISION		( SSRE_FIXED_PRECISION >> 1 )
#define SSRE_FIXED_FLOAT_STEP			( 1.0f / (float)(1 << SSRE_FIXED_PRECISION ) )

/**
 * Common values.
 */
#define SSRE_FIXED_ZERO					( (SSRE_Fixed_t)( 0 ) )
#define SSRE_FIXED_ONE					( (SSRE_Fixed_t)( 1 << SSRE_FIXED_PRECISION ) )
#define SSRE_FIXED_TWO					( (SSRE_Fixed_t)( 2 << SSRE_FIXED_PRECISION ) )
#define SSRE_FIXED_HALF					( (SSRE_Fixed_t)( 2 << ( SSRE_FIXED_PRECISION - 1 ) ) )

/**
 * Float to fixed conversion macro.
 * @param _val float value.
 */
#define SSRE_Fixed_FromFloat( _val )	\
	( (SSRE_Fixed_t)( ( (float)_val ) / SSRE_FIXED_FLOAT_STEP ) )

/**
 * Fixed to float conversion macro.
 */
#define SSRE_Fixed_ToFloat( _val )	\
	( (float)( ( (SSRE_Fixed_t)_val ) * SSRE_FIXED_FLOAT_STEP ) )

/**
 * Fixed point multiply.
 * @param lhs
 * @param rhs
 */
SSRE_Fixed_t SSRE_Fixed_Mul( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs );

/**
 * Fixed point divide.
 * @param lhs
 * @param rhs
 */
SSRE_Fixed_t SSRE_Fixed_Div( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs );

/**
 * Fixed point reciprocal.
 * @param lhs
 * @param rhs
 */
SSRE_Fixed_t SSRE_Fixed_Rcp( SSRE_Fixed_t lhs );

/**
 * Fixed point square root.
 * @param lhs
 */
SSRE_Fixed_t SSRE_Fixed_Sqrt( SSRE_Fixed_t lhs );

#endif
