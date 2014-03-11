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
#include "SSRE_PixelBuffer.h"

#include <stdio.h>
#include <malloc.h>

void SSRE_PixelBuffer_Create( SSRE_PixelBuffer_t* pixelBuffer, int bpp, int w, int h, void* startAddress )
{
	pixelBuffer->bpp = bpp;
	pixelBuffer->w = w;
	pixelBuffer->h = h;

	if( startAddress == NULL )
	{
		pixelBuffer->flags = SSRE_PIXELBUFFER_FLAG_MEMORY_MANAGED;
		pixelBuffer->addr = malloc( ( w * h * bpp ) );
	}
	else
	{
		pixelBuffer->flags = 0;
		pixelBuffer->addr = startAddress;
	}
}

void SSRE_PixelBuffer_Destroy( SSRE_PixelBuffer_t* pixelBuffer )
{
	if( ( pixelBuffer->flags & SSRE_PIXELBUFFER_FLAG_MEMORY_MANAGED ) != 0 )
	{
		free( pixelBuffer->addr );
		pixelBuffer->addr = NULL;
	}
}

void* SSRE_PixelBuffer_Pixel( SSRE_PixelBuffer_t* pixelBuffer, int x, int y )
{
	u8* byteAddr = (u8*)pixelBuffer->addr;
	return byteAddr + ( ( x + y * pixelBuffer->w ) * pixelBuffer->bpp );
}
