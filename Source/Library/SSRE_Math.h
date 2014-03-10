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
#ifndef __SSRE_MATH_H__
#define __SSRE_MATH_H__

#include "SSRE_Types.h"
#include "SSRE_Fixed.h"
#include "SSRE_Vec4.h"

#define SSRE_MATH_INTERSECTION_NONE				( -1 )
#define SSRE_MATH_INTERSECTION_LINE				( 0 )
#define SSRE_MATH_INTERSECTION_SEGMENT			( 1 )


/**
 * Cartesian to Barycentric.
 * @param out Output barycentric coordinates.
 * @param pointA Point a
 * @param pointB Point b
 * @param pointC Point c
 * @param coord Cartesian coordinate.
 */
void SSRE_Math_CartesianToBarycentric23( SSRE_Vec4_t* out, 
									    const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord );
void SSRE_Math_CartesianToBarycentric33( SSRE_Vec4_t* out, 
									    const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord );

/**
 * Barycentric to Cartesian
 * @param out Output cartesian coordinates.
 * @param pointA Point a
 * @param pointB Point b
 * @param pointC Point c
 * @param coord Barycentric coordinate.
 */
void SSRE_Math_BarycentricToCartesian32( SSRE_Vec4_t* out,
									    const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord );
void SSRE_Math_BarycentricToCartesian33( SSRE_Vec4_t* out,
									    const SSRE_Vec4_t* pointA,
									    const SSRE_Vec4_t* pointB,
									    const SSRE_Vec4_t* pointC,
									    const SSRE_Vec4_t* coord );

/**
 * Find line-line intersection.
 * @param out Output coordinate.
 * @param lineA0
 * @param lineA1
 * @param lineB0
 * @param lineB1
 * @return SSRE_MATH_INTERSECTION_NONE if no intersection, 
 *         SSRE_MATH_INTERSECTION_RAY if intersection anywhere, 
 *         SSRE_MATH_INTERSECTION_SEGMENT if intersection is in line segments.
 */
int SSRE_Math_LineLineIntersection2( SSRE_Vec4_t* out, 
									const SSRE_Vec4_t* lineA0, 
									const SSRE_Vec4_t* lineA1, 
									const SSRE_Vec4_t* lineB0,
									const SSRE_Vec4_t* lineB1 );

/**
 * Find line-triangle intersection.
 * @param out Output coordinate.
 * @param lineA0
 * @param lineA0
 * @param point0
 * @param point1
 * @param point2
 * @param wantedIntersection SSRE_MATH_INTERSECTION_RAY or SSRE_MATH_INTERSECTION_SEGMENT.
 * @return SSRE_MATH_INTERSECTION_NONE if no intersection.
 */
int SSRE_Math_LineTriangleIntersection2( SSRE_Vec4_t* out, 
										 const SSRE_Vec4_t* line0, 
										 const SSRE_Vec4_t* line1, 
										 const SSRE_Vec4_t* point0, 
										 const SSRE_Vec4_t* point1, 
										 const SSRE_Vec4_t* point2, 
										 int wantedIntersection );

/**
 * Mix R8G8B8A8 colours.
 * @param num Number of colours.
 * @param colours Array of colours.
 * @param stride Stride.
 * @param amounts Array of amounts (0.0-1.0)
 */
u32 SSRE_Math_LerpColourR8G8B8A8( int num, const void* colours, u32 stride, const SSRE_Fixed_t* amounts );

/**
 * Det2 orientation.
 */
SSRE_Fixed_t SSRE_Math_OrientationTest2( const SSRE_Vec4_t* a, 
                                         const SSRE_Vec4_t* b, 
                                         const SSRE_Vec4_t* c);

#endif

