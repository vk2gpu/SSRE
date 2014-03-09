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
#include "SSRE_VertexProcessor.h"

#include <malloc.h>
#include <assert.h>
#include <stdio.h>

SSRE_VertexProcessor_t* SSRE_VertexProcessor_Create( u32 noofVertices )
{
	SSRE_VertexProcessor_t* vertexProcessor = (SSRE_VertexProcessor_t*)malloc( sizeof( SSRE_VertexProcessor_t ) );

	vertexProcessor->currVertex = 0;
	vertexProcessor->noofVertices = noofVertices;
	vertexProcessor->vertices = (SSRE_Vec4_t*)malloc( noofVertices * sizeof( SSRE_Vec4_t ) );

	return vertexProcessor;
}

void SSRE_VertexProcessor_Destroy( SSRE_VertexProcessor_t* vertexProcessor )
{
	assert( vertexProcessor != NULL );
	assert( vertexProcessor->noofVertices > 0 );
	assert( vertexProcessor->vertices != NULL );

	free( vertexProcessor->vertices );
	free( vertexProcessor );
}

const SSRE_Vec4_t* SSRE_VertexProcessor_Process( SSRE_VertexProcessor_t* vertexProcessor, 
												 u32 noofVertices, 
												 const SSRE_Vec4_t* vertices,
												 SSRE_Mat44_t* matrix )
{
	SSRE_Vec4_t* firstVertex = &vertexProcessor->vertices[ vertexProcessor->currVertex ];
	SSRE_Vec4_t* vertex = firstVertex;
	u32 i = 0;
	SSRE_Fixed_t invW;

	assert( vertexProcessor->currVertex + noofVertices < vertexProcessor->noofVertices );

	for( i = 0; i < noofVertices; ++i, ++vertex )
	{
		// Transform.
		SSRE_Mat44_MultiplyVec3( vertex, matrix, vertices++ );

		// W divide.
		SSRE_Vec4_DivScalar3( vertex, vertex, vertex->w );
	}

	return firstVertex;
}

void SSRE_VertexProcessor_Reset( SSRE_VertexProcessor_t* vertexProcessor )
{
	vertexProcessor->currVertex = 0;
}
