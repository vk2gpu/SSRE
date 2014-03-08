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

#include <assert.h>

void SSRE_Math_CartesianToBarycentric3( SSRE_Vec4_t* out,
									   	const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord )
{
#if 1
	SSRE_Vec4_t tri_tempA;
	SSRE_Vec4_t tri_tempB;
	SSRE_Vec4_t tri_tempC;
	SSRE_Vec4_t cross_ABC;
	SSRE_Vec4_t cross_segment;
	SSRE_Fixed_t invLengthSquared;

	SSRE_Vec4_Sub3( &tri_tempC, pointC, pointA );
	SSRE_Vec4_Sub3( &tri_tempA, pointB, pointA );
	SSRE_Vec4_Cross3( &cross_ABC, &tri_tempA, &tri_tempC );
	invLengthSquared = SSRE_Fixed_Rcp( SSRE_Vec4_MagSqr3( &cross_ABC ) );

	SSRE_Vec4_Sub3( &tri_tempB, coord, pointA );
	SSRE_Vec4_Cross3( &cross_segment, &tri_tempA, &tri_tempB );

	out->z = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );

	SSRE_Vec4_Sub3( &tri_tempA, pointC, pointB );
	SSRE_Vec4_Sub3( &tri_tempB, coord, pointB );
	SSRE_Vec4_Cross3( &cross_segment, &tri_tempA, &tri_tempB );

	out->x = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );

	SSRE_Vec4_Sub3( &tri_tempA, pointA, pointC );
	SSRE_Vec4_Sub3( &tri_tempB, coord, pointC );
	SSRE_Vec4_Cross3( &cross_segment, &tri_tempA, &tri_tempB );

	out->y = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );
#else
	SSRE_Vec4_t tri_BA;
	SSRE_Vec4_t tri_CA;
	SSRE_Vec4_t tri_CB;
	SSRE_Vec4_t tri_AC;
	SSRE_Vec4_t tri_PA;
	SSRE_Vec4_t tri_PB;
	SSRE_Vec4_t tri_PC;
	SSRE_Vec4_t cross_ABC;
	SSRE_Vec4_t cross_BCP;
	SSRE_Vec4_t cross_CAP;
	SSRE_Vec4_t cross_ABP;
	SSRE_Fixed_t invLengthSquared;

	SSRE_Vec4_Sub3( &tri_BA, pointB, pointA );
	SSRE_Vec4_Sub3( &tri_CA, pointC, pointA );
	SSRE_Vec4_Sub3( &tri_CB, pointC, pointB );
	SSRE_Vec4_Sub3( &tri_AC, pointA, pointB );
	SSRE_Vec4_Sub3( &tri_PA, coord, pointA );
	SSRE_Vec4_Sub3( &tri_PB, coord, pointB );
	SSRE_Vec4_Sub3( &tri_PC, coord, pointC );

	SSRE_Vec4_Cross3( &cross_ABC, &tri_BA, &tri_CA );
	SSRE_Vec4_Cross3( &cross_BCP, &tri_CB, &tri_PB );
	SSRE_Vec4_Cross3( &cross_CAP, &tri_AC, &tri_PC );
	SSRE_Vec4_Cross3( &cross_ABP, &tri_BA, &tri_PA );

	invLengthSquared = SSRE_Fixed_Rcp( SSRE_Vec4_MagSqr3( &cross_ABC ) );

	out->x = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_BCP ), invLengthSquared );
	out->y = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_CAP ), invLengthSquared );
	out->z = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_ABP ), invLengthSquared );
#endif
}

void SSRE_Math_BarycentricToCartesian3( SSRE_Vec4_t* out,
									   	const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord )
{
	SSRE_Vec4_t uOut;
	SSRE_Vec4_t vOut;
	SSRE_Vec4_t wOut;

	SSRE_Vec4_MulScalar3( &uOut, pointA, coord->x );
	SSRE_Vec4_MulScalar3( &vOut, pointB, coord->y );
	SSRE_Vec4_MulScalar3( &wOut, pointC, coord->z );
	
	SSRE_Vec4_Add3( out, &uOut, &vOut );
	SSRE_Vec4_Add3( out, out, &wOut );
}

int SSRE_Math_LineLineIntersection2( SSRE_Vec4_t* out,
									 const SSRE_Vec4_t* lineA0, 
									 const SSRE_Vec4_t* lineA1, 
									 const SSRE_Vec4_t* lineB0,
									 const SSRE_Vec4_t* lineB1 )

{
	SSRE_Fixed_t mA, mB, cA, cB, s, t;
	
	mA = SSRE_Fixed_Div( lineA1->y - lineA0->y, lineA1->x - lineA0->x );
	mB = SSRE_Fixed_Div( lineB1->y - lineB0->y, lineB1->x - lineB0->x );

	if( mA == mB )
	{
		return SSRE_MATH_INTERSECTION_NONE;
	}

	cA = lineA0->y - SSRE_Fixed_Mul( mA, lineA0->x );
	cB = lineB0->y - SSRE_Fixed_Mul( mB, lineB0->x );

	// Calculate intersection point.
	out->x = SSRE_Fixed_Div( cB - cA, mA - mB );
	out->y = SSRE_Fixed_Mul( mA, out->x ) + cA;

	// Determine if intersection point is on the lines.
	s = SSRE_Fixed_Div( out->x - lineA0->x , lineA1->x - lineA0->x );
	t = SSRE_Fixed_Div( out->x - lineB0->x , lineB1->x - lineB0->x );

	if( s >= 0 && s <= SSRE_FIXED_ONE &&
		t >= 0 && t <= SSRE_FIXED_ONE )
	{
		return SSRE_MATH_INTERSECTION_SEGMENT;
	}

	return SSRE_MATH_INTERSECTION_LINE;
}

int SSRE_Math_LineTriangleIntersection2( SSRE_Vec4_t* out,
										 const SSRE_Vec4_t* line0, 
										 const SSRE_Vec4_t* line1, 
										 const SSRE_Vec4_t* point0, 
										 const SSRE_Vec4_t* point1, 
										 const SSRE_Vec4_t* point2, 
										 int wantedIntersection )

{
	SSRE_Vec4_t tempOut;
	SSRE_Fixed_t tempDist;
	SSRE_Fixed_t nearestDist = 0x7fffffff;

	assert( wantedIntersection != SSRE_MATH_INTERSECTION_NONE );
	
	if( SSRE_Math_LineLineIntersection2( &tempOut, line0, line1, point0, point1 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempOut, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempOut );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	if( SSRE_Math_LineLineIntersection2( &tempOut, line0, line1, point1, point2 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempOut, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempOut );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	if( SSRE_Math_LineLineIntersection2( &tempOut, line0, line1, point2, point0 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempOut, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempOut );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	// Determine if we found an intersection.
	return nearestDist == 0x7fffffff ? SSRE_MATH_INTERSECTION_NONE : wantedIntersection;
}

u32 SSRE_Math_LerpColourR8G8B8A8( int num, const u32* colours, const SSRE_Fixed_t* amounts )
{
	int i;
	SSRE_Vec4_t col = { 0, 0, 0, 0 };

	assert( 16 == SSRE_FIXED_PRECISION ); // Hard coded to 16 bit precision at the mo.
	
	for( i = 0; i < num; ++i )
	{
		SSRE_Vec4_t in = 
		{
			( colours[i] & 0x000000ff ) << 16,
			( colours[i] & 0x0000ff00 ) << 8,
			( colours[i] & 0x00ff0000 ),
			( colours[i] & 0xff000000 ) >> 8
		};

		SSRE_Vec4_MulScalar( &in, &in, amounts[i] );
		SSRE_Vec4_Add( &col, &col, &in );
	}

	// Floor to int.
	col.x = col.x >> 16;
	col.y = col.y >> 16;
	col.z = col.z >> 16;
	col.w = col.w >> 16;

	// Clamp.
	col.x = col.x > 0xff ? 0xff : col.x;
	col.y = col.y > 0xff ? 0xff : col.y;
	col.z = col.z > 0xff ? 0xff : col.z;
	col.w = col.w > 0xff ? 0xff : col.w;

	// Pack for output.
	return col.x | col.y << 8 | col.z << 16 | col.w << 24;
}
