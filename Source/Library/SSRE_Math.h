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


/**
 * Cartesian to Barycentric (3D)
 * @param out Output barycentric coordinates.
 * @param tri Pointer to 3 coordinates for triangle.
 * @param coord Cartesian coordinate.
 */
void SSRE_Math_CartesianToBarycentric3( SSRE_Vec4_t* out, const SSRE_Vec4_t* tri, const SSRE_Vec4_t* coord );

/**
 * Barycentric to Cartesian (3D)
 * @param out Output cartesian coordinates.
 * @param tri Pointer to 3 coordinates for triangle.
 * @param coord Barycentric coordinate.
 */
void SSRE_Math_BarycentricToCartesian3( SSRE_Vec4_t* out, const SSRE_Vec4_t* tri, const SSRE_Vec4_t* coord );

/**
 * Mix R8G8B8A8 colours.
 * @param num Number of colours.
 * @param colours Array of colours.
 * @param amounts Array of amounts (0.0-1.0)
 */
u32 SSRE_Math_LerpColourR8G8B8A8( int num, const u32* colours, const SSRE_Fixed_t* amounts );

#endif
