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
#include "SSRE_Vec4.h"

void SSRE_Vec4_Add2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x + rhs->x;
	out->y = lhs->y + rhs->y;
}

void SSRE_Vec4_Add3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x + rhs->x;
	out->y = lhs->y + rhs->y;
	out->z = lhs->z + rhs->z;
}

void SSRE_Vec4_Add( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x + rhs->x;
	out->y = lhs->y + rhs->y;
	out->z = lhs->z + rhs->z;
	out->w = lhs->w + rhs->w;
}

void SSRE_Vec4_Sub2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x - rhs->x;
	out->y = lhs->y - rhs->y;
}

void SSRE_Vec4_Sub3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x - rhs->x;
	out->y = lhs->y - rhs->y;
	out->z = lhs->z - rhs->z;
}

void SSRE_Vec4_Sub( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = lhs->x - rhs->x;
	out->y = lhs->y - rhs->y;
	out->z = lhs->z - rhs->z;
	out->w = lhs->w - rhs->w;
}

void SSRE_Vec4_Mul2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs->y );
}

void SSRE_Vec4_Mul3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs->y );
	out->z = SSRE_Fixed_Mul( lhs->z, rhs->z );
}

void SSRE_Vec4_Mul( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs->y );
	out->z = SSRE_Fixed_Mul( lhs->z, rhs->z );
	out->w = SSRE_Fixed_Mul( lhs->w, rhs->w );
}

void SSRE_Vec4_FastMul2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs->y );
}

void SSRE_Vec4_FastMul3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs->y );
	out->z = SSRE_Fixed_FastMul( lhs->z, rhs->z );
}

void SSRE_Vec4_FastMul( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs->x );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs->y );
	out->z = SSRE_Fixed_FastMul( lhs->z, rhs->z );
	out->w = SSRE_Fixed_FastMul( lhs->w, rhs->w );
}

void SSRE_Vec4_Div2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Div( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Div( lhs->y, rhs->y );
}

void SSRE_Vec4_Div3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Div( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Div( lhs->y, rhs->y );
	out->z = SSRE_Fixed_Div( lhs->z, rhs->z );
}

void SSRE_Vec4_Div( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	out->x = SSRE_Fixed_Div( lhs->x, rhs->x );
	out->y = SSRE_Fixed_Div( lhs->y, rhs->y );
	out->z = SSRE_Fixed_Div( lhs->z, rhs->z );
	out->w = SSRE_Fixed_Div( lhs->w, rhs->w );
}

void SSRE_Vec4_MulScalar2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs );
}

void SSRE_Vec4_MulScalar3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs );
	out->z = SSRE_Fixed_Mul( lhs->z, rhs );
}

void SSRE_Vec4_MulScalar( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_Mul( lhs->x, rhs );
	out->y = SSRE_Fixed_Mul( lhs->y, rhs );
	out->z = SSRE_Fixed_Mul( lhs->z, rhs );
	out->w = SSRE_Fixed_Mul( lhs->w, rhs );
}

void SSRE_Vec4_FastMulScalar2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs );
}

void SSRE_Vec4_FastMulScalar3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs );
	out->z = SSRE_Fixed_FastMul( lhs->z, rhs );
}

void SSRE_Vec4_FastMulScalar( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	out->x = SSRE_Fixed_FastMul( lhs->x, rhs );
	out->y = SSRE_Fixed_FastMul( lhs->y, rhs );
	out->z = SSRE_Fixed_FastMul( lhs->z, rhs );
	out->w = SSRE_Fixed_FastMul( lhs->w, rhs );
}

void SSRE_Vec4_DivScalar2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	if( rhs != 0 )
	{
		SSRE_Fixed_t rcp = SSRE_Fixed_Rcp( rhs );
		out->x = SSRE_Fixed_Mul( lhs->x, rcp );
		out->y = SSRE_Fixed_Mul( lhs->y, rcp );
	}
}

void SSRE_Vec4_DivScalar3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	if( rhs != 0 )
	{
		SSRE_Fixed_t rcp = SSRE_Fixed_Rcp( rhs );
		out->x = SSRE_Fixed_Mul( lhs->x, rcp );
		out->y = SSRE_Fixed_Mul( lhs->y, rcp );
		out->z = SSRE_Fixed_Mul( lhs->z, rcp );
	}
}

void SSRE_Vec4_DivScalar( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs )
{
	if( rhs != 0 )
	{
		SSRE_Fixed_t rcp = SSRE_Fixed_Rcp( rhs );
		out->x = SSRE_Fixed_Mul( lhs->x, rcp );
		out->y = SSRE_Fixed_Mul( lhs->y, rcp );
		out->z = SSRE_Fixed_Mul( lhs->z, rcp );
		out->w = SSRE_Fixed_Mul( lhs->w, rcp );
	}
}

void SSRE_Vec4_Rcp2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs )
{
	out->x = SSRE_Fixed_Rcp( lhs->x );
	out->y = SSRE_Fixed_Rcp( lhs->y );
}

void SSRE_Vec4_Rcp3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs )
{
	out->x = SSRE_Fixed_Rcp( lhs->x );
	out->y = SSRE_Fixed_Rcp( lhs->y );
	out->z = SSRE_Fixed_Rcp( lhs->z );
}

void SSRE_Vec4_Rcp( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs )
{
	out->x = SSRE_Fixed_Rcp( lhs->x );
	out->y = SSRE_Fixed_Rcp( lhs->y );
	out->z = SSRE_Fixed_Rcp( lhs->z );
	out->w = SSRE_Fixed_Rcp( lhs->w );
}

SSRE_Fixed_t SSRE_Vec4_Dot2( const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	SSRE_Vec4_t mul;
	SSRE_Vec4_Mul2( &mul, lhs, rhs );
	return mul.x + mul.y;
}

SSRE_Fixed_t SSRE_Vec4_Dot3( const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	SSRE_Vec4_t mul;
	SSRE_Vec4_Mul3( &mul, lhs, rhs );
	return mul.x + mul.y + mul.z;
}

SSRE_Fixed_t SSRE_Vec4_Dot( const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	SSRE_Vec4_t mul;
	SSRE_Vec4_Mul( &mul, lhs, rhs );
	return mul.x + mul.y + mul.z + mul.w;
}

void SSRE_Vec4_Cross2( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs )
{
	assert( out != lhs );

	out->x = -lhs->y;
	out->y = lhs->x;
}

void SSRE_Vec4_Cross3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs )
{
	assert( out != lhs );
	assert( out != rhs );

	out->x = SSRE_Fixed_Mul( lhs->y, rhs->z ) - SSRE_Fixed_Mul( lhs->z, rhs->y );
	out->y = SSRE_Fixed_Mul( lhs->z, rhs->x ) - SSRE_Fixed_Mul( lhs->x, rhs->z );
	out->z = SSRE_Fixed_Mul( lhs->x, rhs->y ) - SSRE_Fixed_Mul( lhs->y, rhs->x );
}

SSRE_Fixed_t SSRE_Vec4_MagSqr2( const SSRE_Vec4_t* lhs )
{
	return SSRE_Vec4_Dot2( lhs, lhs );
}

SSRE_Fixed_t SSRE_Vec4_MagSqr3( const SSRE_Vec4_t* lhs )
{
	return SSRE_Vec4_Dot3( lhs, lhs );
}

SSRE_Fixed_t SSRE_Vec4_MagSqr( const SSRE_Vec4_t* lhs )
{
	return SSRE_Vec4_Dot( lhs, lhs );
}

SSRE_Fixed_t SSRE_Vec4_Mag2( const SSRE_Vec4_t* lhs )
{
	return SSRE_Fixed_Sqrt( SSRE_Vec4_MagSqr2( lhs ) );
}

SSRE_Fixed_t SSRE_Vec4_Mag3( const SSRE_Vec4_t* lhs )
{
	return SSRE_Fixed_Sqrt( SSRE_Vec4_MagSqr3( lhs ) );
}

SSRE_Fixed_t SSRE_Vec4_Mag( const SSRE_Vec4_t* lhs )
{
	return SSRE_Fixed_Sqrt( SSRE_Vec4_MagSqr( lhs ) );
}

void SSRE_Vec4_Nrm2( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs )
{
	SSRE_Fixed_t invMag = SSRE_Fixed_Rcp( SSRE_Vec4_Mag2( lhs ) );
	SSRE_Vec4_MulScalar2( out, lhs, invMag );
}

void SSRE_Vec4_Nrm3( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs )
{
	SSRE_Fixed_t invMag = SSRE_Fixed_Rcp( SSRE_Vec4_Mag3( lhs ) );
	SSRE_Vec4_MulScalar3( out, lhs, invMag );
}

void SSRE_Vec4_Nrm( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs )
{
	SSRE_Fixed_t invMag = SSRE_Fixed_Rcp( SSRE_Vec4_Mag( lhs ) );
	SSRE_Vec4_MulScalar( out, lhs, invMag );
}

void SSRE_Vec4_Less2( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x < rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y < rhs->y ? lhs->y : rhs->y;
}

void SSRE_Vec4_Less3( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x < rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y < rhs->y ? lhs->y : rhs->y;
	out->z = lhs->z < rhs->z ? lhs->z : rhs->z;
}

void SSRE_Vec4_Less( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x < rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y < rhs->y ? lhs->y : rhs->y;
	out->z = lhs->z < rhs->z ? lhs->z : rhs->z;
	out->w = lhs->w < rhs->w ? lhs->w : rhs->w;
}

void SSRE_Vec4_Greater2( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x > rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y > rhs->y ? lhs->y : rhs->y;
}

void SSRE_Vec4_Greater3( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x > rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y > rhs->y ? lhs->y : rhs->y;
	out->z = lhs->z > rhs->z ? lhs->z : rhs->z;
}

void SSRE_Vec4_Greater( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs, SSRE_Vec4_t* rhs )
{
	out->x = lhs->x > rhs->x ? lhs->x : rhs->x;
	out->y = lhs->y > rhs->y ? lhs->y : rhs->y;
	out->z = lhs->z > rhs->z ? lhs->z : rhs->z;
	out->w = lhs->w > rhs->w ? lhs->w : rhs->w;
}
