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
#include "SSRE_Fixed.h"

SSRE_Fixed_t SSRE_Fixed_Mul( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs )
{
	s64 value = (s64)lhs * (s64)rhs;
	return (SSRE_Fixed_t)( ( value ) >> SSRE_FIXED_PRECISION );
}

SSRE_Fixed_t SSRE_Fixed_Div( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs )
{
	return (SSRE_Fixed_t)( ( ( (s64)lhs << SSRE_FIXED_DOUBLE_PRECISION ) / (s64)rhs ) >> SSRE_FIXED_PRECISION );
}

SSRE_Fixed_t SSRE_Fixed_Rcp( SSRE_Fixed_t lhs )
{
	// TODO: Don't use divide...can to better?
	if( lhs != 0 )
	{
		return SSRE_Fixed_Div( SSRE_FIXED_ONE, lhs );
	}
	return lhs;
}

SSRE_Fixed_t SSRE_Fixed_Sqrt( SSRE_Fixed_t lhs )
{
	register u64 v = lhs;
	register u64 x = v >> 1;
	register u64 a = 0;

	if( v > 0 && x != 0 )
	{
		do
		{
			a = ( ( v << SSRE_FIXED_DOUBLE_PRECISION ) / x ) >> SSRE_FIXED_PRECISION;
			x = ( ( ( x + a ) << SSRE_FIXED_DOUBLE_PRECISION ) / SSRE_FIXED_TWO ) >> SSRE_FIXED_PRECISION;
		}
		while( ( x * x ) > ( v << SSRE_FIXED_PRECISION ) );

		return (SSRE_Fixed_t)x;
	}

	return 0;
}
