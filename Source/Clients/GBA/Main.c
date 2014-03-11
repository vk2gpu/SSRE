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

#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>

#include "SSRE.h"

int main() 
{
	SSRE_MatrixStack_t matrixStack;
	SSRE_VertexProcessor_t vertexProcessor;
	SSRE_PixelBuffer_t buffer; 

	// Set up the interrupt handlers
	irqInit();

	// Enable Vblank Interrupt to allow VblankIntrWait
	irqEnable(IRQ_VBLANK);

	// Allow Interrupts
	REG_IME = 1;

	SSRE_MatrixStack_Create( &matrixStack, 16 );
	SSRE_VertexProcessor_Create( &vertexProcessor, 256, SSRE_VERTEX_HAS_POSITION | 
	                                                    SSRE_VERTEX_HAS_COLOUR |
	                                                    SSRE_VERTEX_HAS_UV, 
														sizeof( SSRE_VertexPCT_t ) );
	SSRE_PixelBuffer_Create( &buffer, 2, SCREEN_WIDTH, SCREEN_HEIGHT, MODE3_FB );

	// screen mode & background to display
	SetMode( MODE_3 | BG2_ON );

	while(1)
	{
		VBlankIntrWait();
		memset( buffer.addr, 0xff, sizeof( u16 ) * buffer.w * buffer.h );

	}
}
