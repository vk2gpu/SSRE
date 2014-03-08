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
#include "SSRE_Math.h"

void SSRE_Math_CartesianToBarycentric3( SSRE_Vec4_t* out, const SSRE_Vec4_t* tri, const SSRE_Vec4_t* coord )
{
	SSRE_Vec4_t p1minusp0;
	SSRE_Vec4_t p2minusp0;
	SSRE_Vec4_t p0minusCoord;
	SSRE_Vec4_t p1minusCoord;
	SSRE_Vec4_t p2minusCoord;
	SSRE_Vec4_t uCross;
	SSRE_Vec4_t vCross;
	SSRE_Vec4_t wCross;
	SSRE_Vec4_t triAreaCross;
	SSRE_Fixed_t invTriArea;

	SSRE_Vec4_Sub( &p1minusp0, &tri[1], &tri[0] );
	SSRE_Vec4_Sub( &p2minusp0, &tri[2], &tri[0] );
	SSRE_Vec4_Sub( &p0minusCoord, &tri[0], coord );
	SSRE_Vec4_Sub( &p1minusCoord, &tri[1], coord );
	SSRE_Vec4_Sub( &p2minusCoord, &tri[2], coord );
	SSRE_Vec4_Cross3( &uCross, &p1minusCoord, &p2minusCoord );
	SSRE_Vec4_Cross3( &vCross, &p0minusCoord, &p2minusCoord );
	SSRE_Vec4_Cross3( &wCross, &p0minusCoord, &p1minusCoord );
	SSRE_Vec4_Cross3( &triAreaCross, &p1minusp0, &p2minusp0 );
	invTriArea = SSRE_Fixed_Rcp( SSRE_Vec4_Mag3( &triAreaCross ) );
	
	out->x = SSRE_Fixed_Mul( SSRE_Vec4_Mag3( &uCross ), invTriArea );
	out->y = SSRE_Fixed_Mul( SSRE_Vec4_Mag3( &vCross ), invTriArea );
	out->z = SSRE_Fixed_Mul( SSRE_Vec4_Mag3( &wCross ), invTriArea );
	out->w = 0;
}

void SSRE_Math_BarycentricToCartesian3( SSRE_Vec4_t* out, const SSRE_Vec4_t* tri, const SSRE_Vec4_t* coord )
{
	SSRE_Vec4_t uOut;
	SSRE_Vec4_t vOut;
	SSRE_Vec4_t wOut;

	SSRE_Vec4_MulScalar( &uOut, &tri[0], coord->x );
	SSRE_Vec4_MulScalar( &vOut, &tri[1], coord->y );
	SSRE_Vec4_MulScalar( &wOut, &tri[2], coord->z );
	
	SSRE_Vec4_Add( out, &uOut, &vOut );
	SSRE_Vec4_Add( out, out, &wOut );
}
