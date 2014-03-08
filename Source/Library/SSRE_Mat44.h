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
#ifndef __SSRE_MAT44_H__
#define __SSRE_MAT44_H__

#include "SSRE_Vec4.h"

/**
 * Fixed point type.
 */
typedef struct
{
	SSRE_Vec4_t rows[4];
} SSRE_Mat44_t;


/**
 * Identity.
 * @param out
 */
void SSRE_Mat44_Identity( SSRE_Mat44_t* out );

/**
 * Rotation matrix.
 * @param out
 */
void SSRE_Mat44_Rotation( SSRE_Mat44_t* out, int yaw, int pitch, int roll );

/**
* Get column.
* @param out
* @param in
* @param column
*/
void SSRE_Mat44_GetColumn( SSRE_Vec4_t* out, const SSRE_Mat44_t* in, int column );

/**
 * Multiple.
 * @param out
 */
void SSRE_Mat44_Multiply( SSRE_Mat44_t* out, const SSRE_Mat44_t* lhs, const SSRE_Mat44_t* rhs );



#endif

