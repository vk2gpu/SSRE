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
#ifndef __SSRE_VERTEX_H__
#define __SSRE_VERTEX_H__

#include "SSRE_Vec4.h"

#define	SSRE_VERTEX_HAS_POSITION				0x00000001
#define	SSRE_VERTEX_HAS_COLOUR					0x00000002
#define	SSRE_VERTEX_HAS_UV						0x00000004

/**
 * SSRE_VertexP_t
 */
typedef struct
{
	SSRE_Vec4_t pos;
} SSRE_VertexP_t;

/**
 * SSRE_VertexPC_t
 */
typedef struct
{
	SSRE_Vec4_t pos;
	u32			col;
} SSRE_VertexPC_t;

/**
 * SSRE_VertexPT_t
 */
typedef struct
{
	SSRE_Vec4_t pos;
	u8			u;
	u8			v;
} SSRE_VertexPT_t;

/**
 * SSRE_VertexPCT_t
 */
typedef struct
{
	SSRE_Vec4_t pos;
	u32			col;
	u8			u;
	u8			v;
} SSRE_VertexPCT_t;

#endif
