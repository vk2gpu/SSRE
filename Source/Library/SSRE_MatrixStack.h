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
#ifndef __SSRE_MAT44_STACK_H__
#define __SSRE_MAT44_STACK_H__

#include "SSRE_Mat44.h"

/**
 * Mat44 stack
 */
typedef struct
{
	u32 noofMatrices;
	u32 currMatrix;
	SSRE_Mat44_t* matrices;
} SSRE_MatrixStack_t;

/**
 * Create matrix stack.
 * @param noofVertices Number of vertices tobe able to cope.
 */
SSRE_MatrixStack_t* SSRE_MatrixStack_Create( u32 noofMatrices );

/**
 * Destroy matrix stack.
 * @param matrixStack Matrix stack.
 */
void SSRE_MatrixStack_Destroy( SSRE_MatrixStack_t* matrixStack );

/**
 * Push matrix.
 * @param matrixStack Matrix stack.
 */
void SSRE_MatrixStack_Push( SSRE_MatrixStack_t* matrixStack, const SSRE_Mat44_t* in );

/**
 * Pop matrix.
 * @param matrixStack Matrix stack.
 * @param noofLevels Number of levels to pop.
 */
void SSRE_MatrixStack_Pop( SSRE_MatrixStack_t* matrixStack, u32 noofLevels );

/**
 * Get matrix.
 * @param out Matrix on stack.
 * @param matrixStack Matrix stack.
 */
void SSRE_MatrixStack_Get( SSRE_Mat44_t* out, const SSRE_MatrixStack_t* matrixStack );



#endif
