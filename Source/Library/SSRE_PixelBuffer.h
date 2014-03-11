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
#ifndef __SSRE_PIXELBUFFER_H__
#define __SSRE_PIXELBUFFER_H__

#include "SSRE_Types.h"

/**
 * Pixel buffer.
 */
typedef struct
{
	int		bpp;
	int		w;
	int		h;
	u32		flags;
	void*	addr;
} SSRE_PixelBuffer_t;

// Pixel buffer manages it's own memory.
#define SSRE_PIXELBUFFER_FLAG_MEMORY_MANAGED		( 0x000000001 )

/**
 * Create pixel buffer.
 * @param pixelBuffer Output pixel buffer.
 * @param bpp Bytes per pixel.
 * @param w Width
 * @param h Height
 * @param startAddress Start address. NULL if you want to create one.
 */
void SSRE_PixelBuffer_Create( SSRE_PixelBuffer_t* pixelBuffer, int bpp, int w, int h, void* startAddress );

/**
 * Destroy pixel buffer.
 * @param pixelBuffer Pixel buffer.
 */
void SSRE_PixelBuffer_Destroy( SSRE_PixelBuffer_t* pixelBuffer );

/**
 * Get pointer to pixel.
 * @param pixelBuffer Pixel buffer.
 * @param x
 * @param y
 */
void* SSRE_PixelBuffer_Pixel( SSRE_PixelBuffer_t* pixelBuffer, int x, int y ); 

#endif 
