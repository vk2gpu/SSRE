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
#include <stdlib.h>

SSRE_VertexProcessor_t* SSRE_VertexProcessor_Create( u32 noofVertices, u32 vertexType, u32 vertexStride )
{
	SSRE_VertexProcessor_t* vertexProcessor = (SSRE_VertexProcessor_t*)malloc( sizeof( SSRE_VertexProcessor_t ) );

	vertexProcessor->currVertex = 0;
	vertexProcessor->noofVertices = noofVertices;
	vertexProcessor->vertexType = vertexType;
	vertexProcessor->vertexStride = vertexStride;
	vertexProcessor->vertices = (SSRE_Vec4_t*)malloc( noofVertices * sizeof( vertexStride ) );

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

const void* SSRE_VertexProcessor_Process( SSRE_VertexProcessor_t* vertexProcessor, 
												 u32 noofVertices, 
												 const void* vertices,
												 SSRE_Mat44_t* matrix )
{
	char* firstVertex;
	char* outVertex;
	char* inVertex;
	u32 i = 0;
	u32 offset = 0;

	assert( vertexProcessor != NULL );
	assert( vertexProcessor->currVertex + noofVertices < vertexProcessor->noofVertices );

	firstVertex = (char*)vertexProcessor->vertices + ( vertexProcessor->currVertex * vertexProcessor->vertexStride );
	
	// Position processing.
	if( ( vertexProcessor->vertexType & SSRE_VERTEX_HAS_POSITION ) != 0 )
	{
		outVertex = firstVertex + offset;
		inVertex = (char*)vertices + offset;
		for( i = 0; i < noofVertices; ++i )
		{
			// Transform.
			SSRE_Mat44_MultiplyVec3( (SSRE_Vec4_t*)outVertex, matrix, (SSRE_Vec4_t*)inVertex );

			// W divide.
			SSRE_Vec4_DivScalar3( (SSRE_Vec4_t*)outVertex, (SSRE_Vec4_t*)outVertex, ((SSRE_Vec4_t*)outVertex)->w );

			// Advance.
			outVertex += vertexProcessor->vertexStride;
			inVertex += vertexProcessor->vertexStride;
		}

		offset += sizeof( SSRE_Vec4_t );
	}

	// Colour processing.
	if( ( vertexProcessor->vertexType & SSRE_VERTEX_HAS_COLOUR ) != 0 )
	{
		outVertex = firstVertex + offset;
		inVertex = (char*)vertices + offset;
		for( i = 0; i < noofVertices; ++i )
		{
			// Simple copy.
			*((u32*)outVertex) = *((u32*)inVertex);

			// Advance.
			outVertex += vertexProcessor->vertexStride;
			inVertex += vertexProcessor->vertexStride;
		}

		offset += sizeof( u32 );
	}

	// UV processing.
	if( ( vertexProcessor->vertexType & SSRE_VERTEX_HAS_UV ) != 0 )
	{
		outVertex = firstVertex + offset;
		inVertex = (char*)vertices + offset;
		for( i = 0; i < noofVertices; ++i )
		{
			// Simple copy.
			*((u16*)outVertex) = *((u16*)inVertex);

			// Advance.
			outVertex += vertexProcessor->vertexStride;
			inVertex += vertexProcessor->vertexStride;
		}

		offset += sizeof( u16 );
	}

	vertexProcessor->currVertex += noofVertices;

	return firstVertex;
}

static int _SSRE_VertexProcessor_SortTriangles_CmpFunc(const void* inA, const void* inB)
{
	const SSRE_Vec4_t* triA = (const SSRE_Vec4_t*)inA;
	const SSRE_Vec4_t* triB = (const SSRE_Vec4_t*)inB;
	SSRE_Fixed_t a = triA[0].z;
	SSRE_Fixed_t b = triB[0].z;

	if( triA[1].z > a )
	{
		a = triA[1].z;
	}

	if( triA[2].z > a )
	{
		a = triA[2].z;
	}

	if( triB[1].z > b )
	{
		b = triB[1].z;
	}

	if( triB[2].z > b )
	{
		b = triB[2].z;
	}

	return b - a;
}

void SSRE_VertexProcessor_SortTriangles( SSRE_VertexProcessor_t* vertexProcessor )
{
	qsort( vertexProcessor->vertices, vertexProcessor->currVertex / 3, vertexProcessor->vertexStride * 3, _SSRE_VertexProcessor_SortTriangles_CmpFunc );
}

void SSRE_VertexProcessor_Reset( SSRE_VertexProcessor_t* vertexProcessor )
{
	vertexProcessor->currVertex = 0;
}
