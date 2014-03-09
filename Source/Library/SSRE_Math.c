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

void SSRE_Math_CartesianToBarycentric23( SSRE_Vec4_t* out,
									   	const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord )
{
	SSRE_Vec4_t tri_tempA;
	SSRE_Vec4_t tri_tempB;
	SSRE_Vec4_t tri_tempC;
	SSRE_Vec4_t cross_ABC;
	SSRE_Vec4_t cross_segment;
	SSRE_Fixed_t invLengthSquared;

	SSRE_Vec4_Sub3( &tri_tempC, pointC, pointA );
	SSRE_Vec4_Sub3( &tri_tempA, pointB, pointA );
	SSRE_Vec4_Cross2( &cross_ABC, &tri_tempA, &tri_tempC );
	invLengthSquared = SSRE_Fixed_Rcp( SSRE_Vec4_MagSqr3( &cross_ABC ) );

	SSRE_Vec4_Sub3( &tri_tempB, coord, pointA );
	SSRE_Vec4_Cross2( &cross_segment, &tri_tempA, &tri_tempB );

	out->z = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );

	SSRE_Vec4_Sub3( &tri_tempA, pointC, pointB );
	SSRE_Vec4_Sub3( &tri_tempB, coord, pointB );
	SSRE_Vec4_Cross2( &cross_segment, &tri_tempA, &tri_tempB );

	out->x = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );

	SSRE_Vec4_Sub3( &tri_tempA, pointA, pointC );
	SSRE_Vec4_Sub3( &tri_tempB, coord, pointC );
	SSRE_Vec4_Cross2( &cross_segment, &tri_tempA, &tri_tempB );

	out->y = SSRE_Fixed_Mul( SSRE_Vec4_Dot3( &cross_ABC, &cross_segment ), invLengthSquared );
}

void SSRE_Math_CartesianToBarycentric33( SSRE_Vec4_t* out,
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

void SSRE_Math_BarycentricToCartesian32( SSRE_Vec4_t* out,
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
	
	SSRE_Vec4_Add2( out, &uOut, &vOut );
	SSRE_Vec4_Add2( out, out, &wOut );
}

void SSRE_Math_BarycentricToCartesian33( SSRE_Vec4_t* out,
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
	const SSRE_Fixed_t epsilon = SSRE_FIXED_SMALLEST_VALUE;
	const SSRE_Fixed_t Aa = lineA1->y - lineA0->y;
	const SSRE_Fixed_t Ab = lineA0->x - lineA1->x;
	const SSRE_Fixed_t Ac = SSRE_Fixed_Mul( Aa, lineA0->x ) + SSRE_Fixed_Mul( Ab, lineA0->y );
	const SSRE_Fixed_t Ba = lineB1->y - lineB0->y;
	const SSRE_Fixed_t Bb = lineB0->x - lineB1->x;
	const SSRE_Fixed_t Bc = SSRE_Fixed_Mul( Ba, lineB0->x ) + SSRE_Fixed_Mul( Bb, lineB0->y );
	const SSRE_Fixed_t det = SSRE_Fixed_Mul( Aa, Bb ) - SSRE_Fixed_Mul( Ba, Ab );
	SSRE_Fixed_t s, t, sDenom, tDenom;

	if( det == 0 )
	{
		return SSRE_MATH_INTERSECTION_NONE;
	}
	
	out->x = SSRE_Fixed_Mul( Bb, Ac ) - SSRE_Fixed_Mul( Ab, Bc );
	out->y = SSRE_Fixed_Mul( Aa, Bc ) - SSRE_Fixed_Mul( Ba, Ac );
	SSRE_Vec4_DivScalar2( out, out, det );

	// Check point in line A.
	if( Ab != 0 )
	{
		// y = mx + c; 
		s = SSRE_Fixed_Div( out->x - lineA0->x, -Ab );
	}
	else
	{
		// x = my + c;
		s = SSRE_Fixed_Div( out->y - lineA0->y, Aa );
	}

	// Check point in line B
	if( Bb != 0 )
	{
		// y = mx + c; 
		t = SSRE_Fixed_Div( out->x - lineB0->x, -Bb );
	}
	else
	{
		// x = my + c;
		t = SSRE_Fixed_Div( out->y - lineB0->y, Ba );
	}

	if( s >= -epsilon && s <= ( SSRE_FIXED_ONE + epsilon ) &&
		t >= -epsilon && t <= ( SSRE_FIXED_ONE + epsilon ) )
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
	SSRE_Vec4_t tempDistWorking;
	SSRE_Fixed_t tempDist;
	SSRE_Fixed_t nearestDist = 0x7fffffff;

	assert( wantedIntersection != SSRE_MATH_INTERSECTION_NONE );
	
	if( SSRE_Math_LineLineIntersection2( &tempOut, point0, point1, line0, line1 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempDistWorking, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempDistWorking );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	if( SSRE_Math_LineLineIntersection2( &tempOut, point1, point2, line0, line1 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempDistWorking, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempDistWorking );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	if( SSRE_Math_LineLineIntersection2( &tempOut, point2, point0, line0, line1 ) == wantedIntersection )
	{
		SSRE_Vec4_Sub2( &tempDistWorking, &tempOut, line0 );
		tempDist = SSRE_Vec4_MagSqr2( &tempDistWorking );
		if( tempDist < nearestDist )
		{
			nearestDist = tempDist;
			*out = tempOut;
		}
	}

	// Determine if we found an intersection.
	return nearestDist == 0x7fffffff ? SSRE_MATH_INTERSECTION_NONE : wantedIntersection;
}

u32 SSRE_Math_LerpColourR8G8B8A8( int num, const char* colours, u32 stride, const SSRE_Fixed_t* amounts )
{
	int i;
	SSRE_Vec4_t col = { 0, 0, 0, 0 };
	
	for( i = 0; i < num; ++i )
	{
		SSRE_Vec4_t in;
		in.x = ( *((u32*)colours) & 0x000000ff ) << SSRE_FIXED_PRECISION;
		in.y = ( *((u32*)colours) & 0x0000ff00 ) >> 8 << SSRE_FIXED_PRECISION;
		in.z = ( *((u32*)colours) & 0x00ff0000 ) >> 16 << SSRE_FIXED_PRECISION;
		in.w = ( *((u32*)colours) & 0xff000000 ) >> 24 << SSRE_FIXED_PRECISION;

		SSRE_Vec4_MulScalar( &in, &in, amounts[i] );
		SSRE_Vec4_Add( &col, &col, &in );

		colours += stride;
	}

	// Floor to int.
	col.x = col.x >> SSRE_FIXED_PRECISION;
	col.y = col.y >> SSRE_FIXED_PRECISION;
	col.z = col.z >> SSRE_FIXED_PRECISION;
	col.w = col.w >> SSRE_FIXED_PRECISION;

	// Clamp.
	col.x = ( col.x > 0xff ? 0xff : col.x ) & 0xff;
	col.y = ( col.y > 0xff ? 0xff : col.y ) & 0xff;
	col.z = ( col.z > 0xff ? 0xff : col.z ) & 0xff;
	col.w = ( col.w > 0xff ? 0xff : col.w ) & 0xff;

	// Pack for output.
	return col.x | col.y << 8 | col.z << 16 | col.w << 24;
}
