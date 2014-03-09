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
#ifndef __SSRE_VERTEXPROCESSOR_H__
#define __SSRE_VERTEXPROCESSOR_H__

#include "SSRE_Vec4.h"
#include "SSRE_Mat44.h"

/**
 * Vertex processor
 */
typedef struct
{
	u32 noofVertices;
	u32 currVertex;
	SSRE_Vec4_t* vertices;


} SSRE_VertexProcessor_t;

/**
 * Create vertex processor.
 * @param noofVertices Number of vertices tobe able to cope.
 */
SSRE_VertexProcessor_t* SSRE_VertexProcessor_Create( u32 noofVertices );

/**
 * Destroy vertex processor.
 * @param vertexProcessor The vertex processor.
 */
void SSRE_VertexProcessor_Destroy( SSRE_VertexProcessor_t* vertexProcessor );

/**
 * Process vertices.
 * @param vertexProcessor The vertex processor.
 * @param noofVertices Number of vertices to process.
 * @param vertices Array of vertices.
 * @param matrix Matrix to process with.
 * @return First vertex processed.
 */
const SSRE_Vec4_t* SSRE_VertexProcessor_Process( SSRE_VertexProcessor_t* vertexProcessor, 
												 u32 noofVertices, 
												 const SSRE_Vec4_t* vertices,
												 SSRE_Mat44_t* matrix );

/**
 * Reset vertex processor.
 * @param vertexProcessor The vertex processor.
 */
void SSRE_VertexProcessor_Reset( SSRE_VertexProcessor_t* vertexProcessor );

/**
 * 
 */

#endif

