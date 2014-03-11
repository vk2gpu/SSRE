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
#include "SSRE_MatrixStack.h"

#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void SSRE_MatrixStack_Create( SSRE_MatrixStack_t* matrixStack, u32 noofMatrices )
{
	matrixStack->currMatrix = 0;
	matrixStack->noofMatrices = noofMatrices;
	matrixStack->matrices = (SSRE_Mat44_t*)malloc( noofMatrices * sizeof( SSRE_Mat44_t ) );

	// Stick an identity at the top.
	SSRE_Mat44_Identity( &matrixStack->matrices[0] );
}

void SSRE_MatrixStack_Destroy( SSRE_MatrixStack_t* matrixStack )
{
	assert( matrixStack != NULL );
	assert( matrixStack->noofMatrices > 0 );
	assert( matrixStack->matrices != NULL );

	free( matrixStack->matrices );
	matrixStack->matrices = NULL;
}

void SSRE_MatrixStack_Push( SSRE_MatrixStack_t* matrixStack, const SSRE_Mat44_t* in )
{
	SSRE_Mat44_t* currMatrix = &matrixStack->matrices[ matrixStack->currMatrix ];
	SSRE_Mat44_t* nextMatrix = &matrixStack->matrices[ ++matrixStack->currMatrix ];
	assert( matrixStack->currMatrix < ( matrixStack->noofMatrices - 1 ) );

	SSRE_Mat44_Multiply( nextMatrix, in, currMatrix );
}

void SSRE_MatrixStack_Pop( SSRE_MatrixStack_t* matrixStack, u32 noofLevels )
{
	matrixStack->currMatrix -= noofLevels;
}

void SSRE_MatrixStack_Get( SSRE_Mat44_t* out, const SSRE_MatrixStack_t* matrixStack )
{
	*out = matrixStack->matrices[ matrixStack->currMatrix ];
}
