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

#include <SDL.h>
#include <SSRE.h>

#include <memory.h>
#include <malloc.h>
#include <math.h>

typedef struct
{
	u32* pixels;
	int w;
	int h;
} PixelBuffer_t;

void simpleTestDraw( u32* pixels, int width, int height )
{
	int x, y;
	SSRE_Vec4_t pixel;
	SSRE_Vec4_t pixelBarycentric;
	SSRE_Vec4_t halfRes;
	SSRE_Vec4_t tri[3];
	u32 colours[3] = 
	{
		0xff0000ff,
		0x00ff00ff,
		0x0000ffff,
	};

	// Setup half res.
	halfRes.x = ( width << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.y = ( height << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.z = 1;
	halfRes.w = 1;

	
	// Setup simple triangle.
	tri[0].x = SSRE_Fixed_FromFloat( 0.0f );
	tri[0].y = SSRE_Fixed_FromFloat( -1.0f );
	tri[0].z = 0;
	tri[0].w = 0;

	tri[1].x = SSRE_Fixed_FromFloat( 0.5f );
	tri[1].y = SSRE_Fixed_FromFloat( 0.5f );
	tri[1].z = 0;
	tri[1].w = 0;

	tri[2].x = SSRE_Fixed_FromFloat( -0.5f );
	tri[2].y = SSRE_Fixed_FromFloat( 0.5f );
	tri[2].z = 0;
	tri[2].w = 0;

	// Iterate over all pixels and check if we are in bounds or not.
	for( y = 0; y < height; ++y )
	{
		for( x = 0; x < width; ++x )
		{
			// Convert screen space to clip space to keep from going beyond our 16 bit range.
			pixel.x = x << SSRE_FIXED_PRECISION;
			pixel.y = y << SSRE_FIXED_PRECISION;
			pixel.z = 1;
			pixel.w = 1;

			// Offset.
			SSRE_Vec4_Sub( &pixel, &pixel, &halfRes );

			// Scale up.
			SSRE_Vec4_Div( &pixel, &pixel, &halfRes );
		
			SSRE_Math_CartesianToBarycentric3( &pixelBarycentric, &tri[0], &tri[1], &tri[2], &pixel );
			
			if( pixelBarycentric.x >= 0 && 
				pixelBarycentric.y >= 0 && 
				pixelBarycentric.z >= 0 &&
				pixelBarycentric.x <= SSRE_FIXED_ONE && 
				pixelBarycentric.y <= SSRE_FIXED_ONE && 
				pixelBarycentric.z <= SSRE_FIXED_ONE ) 
			{
				u32 outColour = SSRE_Math_LerpColourR8G8B8A8( 3, colours, &pixelBarycentric.x );
				*pixels++ = outColour;
			}
		}
	}	
}

void simpleTestDrawRegioned( u32* pixels, int width, int height )
{
	int x, y;
	u32* outPixels;
	SSRE_Vec4_t pixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t pixelBarycentric = { 0, 0, 0, 0 };
	SSRE_Vec4_t halfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t invHalfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t tri[3];
	SSRE_Vec4_t minCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t minPixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxPixel = { 0, 0, 0, 0 };
	u32 colours[3] = 
	{
		0xff0000ff,
		0x00ff00ff,
		0x0000ffff,
	};

	// Setup half res.
	halfRes.x = ( width << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.y = ( height << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.z = 1;
	halfRes.w = 1;

	// Setup inv res.
	SSRE_Vec4_Rcp2( &invHalfRes, &halfRes );

	// Setup simple triangle.
	tri[0].x = SSRE_Fixed_FromFloat( 0.0f );
	tri[0].y = SSRE_Fixed_FromFloat( -0.5f );
	tri[0].z = 0;
	tri[0].w = 0;

	tri[1].x = SSRE_Fixed_FromFloat( 0.5f );
	tri[1].y = SSRE_Fixed_FromFloat( 0.5f );
	tri[1].z = 0;
	tri[1].w = 0;

	tri[2].x = SSRE_Fixed_FromFloat( -0.5f );
	tri[2].y = SSRE_Fixed_FromFloat( 0.5f );
	tri[2].z = 0;
	tri[2].w = 0;

	// Find min/max width and height so we don't try to render to the full screen.
	SSRE_Vec4_Less2( &minCoord, &tri[0], &tri[1] );
	SSRE_Vec4_Less2( &minCoord, &minCoord, &tri[2] );
	SSRE_Vec4_Greater2( &maxCoord, &tri[0], &tri[1] );
	SSRE_Vec4_Greater2( &maxCoord, &maxCoord, &tri[2] );

	// Scale down.
	SSRE_Vec4_Mul2( &minPixel, &minCoord, &halfRes );
	SSRE_Vec4_Mul2( &maxPixel, &maxCoord, &halfRes );

	// Offset.
	SSRE_Vec4_Add2( &minPixel, &minPixel, &halfRes );
	SSRE_Vec4_Add2( &maxPixel, &maxPixel, &halfRes );

	minPixel.x >>= SSRE_FIXED_PRECISION;
	minPixel.y >>= SSRE_FIXED_PRECISION;
	maxPixel.x >>= SSRE_FIXED_PRECISION;
	maxPixel.y >>= SSRE_FIXED_PRECISION;


	// Determine if any primitives lie on this scanline.
	for( y = minPixel.y, pixel.y = minCoord.y; 
		 y <= maxPixel.y;
		 ++y, pixel.y += invHalfRes.y )
	{
		outPixels = &pixels[ minPixel.x + y * width ];

		for( x = minPixel.x, pixel.x = minCoord.x; 
			 x <= maxPixel.x; 
			 ++x, pixel.x += invHalfRes.x, ++outPixels )
		{
			SSRE_Math_CartesianToBarycentric3( &pixelBarycentric, &tri[0], &tri[1], &tri[2], &pixel );
			
			if( pixelBarycentric.x >= 0 && 
				pixelBarycentric.y >= 0 && 
				pixelBarycentric.z >= 0 &&
				pixelBarycentric.x <= SSRE_FIXED_ONE && 
				pixelBarycentric.y <= SSRE_FIXED_ONE && 
				pixelBarycentric.z <= SSRE_FIXED_ONE ) 
			{
				*outPixels = SSRE_Math_LerpColourR8G8B8A8( 3, colours, &pixelBarycentric.x );
			}
		}
	}
}

void drawTriangle( PixelBuffer_t* buffer, SSRE_Vec4_t* points, u32 colour )
{
	int x, y;
	u32* outPixels;
	SSRE_Vec4_t pixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t pixelBarycentric = { 0, 0, 0, 0 };
	SSRE_Vec4_t halfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t invHalfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t minCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t minPixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxPixel = { 0, 0, 0, 0 };

	// Setup half res.
	halfRes.x = ( buffer->w << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.y = ( buffer->h << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.z = 1;
	halfRes.w = 1;

	// Setup inv res.
	SSRE_Vec4_Rcp2( &invHalfRes, &halfRes );

	// Find min/max width and height so we don't try to render to the full screen.
	SSRE_Vec4_Less2( &minCoord, &points[0], &points[1] );
	SSRE_Vec4_Less2( &minCoord, &minCoord, &points[2] );
	SSRE_Vec4_Greater2( &maxCoord, &points[0], &points[1] );
	SSRE_Vec4_Greater2( &maxCoord, &maxCoord, &points[2] );

	// Scale down.
	SSRE_Vec4_Mul2( &minPixel, &minCoord, &halfRes );
	SSRE_Vec4_Mul2( &maxPixel, &maxCoord, &halfRes );

	// Offset.
	SSRE_Vec4_Add2( &minPixel, &minPixel, &halfRes );
	SSRE_Vec4_Add2( &maxPixel, &maxPixel, &halfRes );

	// Back to integers.
	minPixel.x >>= SSRE_FIXED_PRECISION;
	minPixel.y >>= SSRE_FIXED_PRECISION;
	maxPixel.x >>= SSRE_FIXED_PRECISION;
	maxPixel.y >>= SSRE_FIXED_PRECISION;


	// Determine if any primitives lie on this scanline.
	for( y = minPixel.y, pixel.y = minCoord.y; 
		 y <= maxPixel.y;
		 ++y, pixel.y += invHalfRes.y )
	{
		outPixels = &buffer->pixels[ minPixel.x + y * buffer->w ];

		for( x = minPixel.x, pixel.x = minCoord.x; 
			 x <= maxPixel.x; 
			 ++x, pixel.x += invHalfRes.x, ++outPixels )
		{
			SSRE_Math_CartesianToBarycentric3( &pixelBarycentric, &points[0], &points[1], &points[2], &pixel );
			
			if( pixelBarycentric.x >= 0 && 
				pixelBarycentric.y >= 0 && 
				pixelBarycentric.z >= 0 &&
				pixelBarycentric.x <= SSRE_FIXED_ONE && 
				pixelBarycentric.y <= SSRE_FIXED_ONE && 
				pixelBarycentric.z <= SSRE_FIXED_ONE ) 
			{
				*outPixels = colour;
			}
		}
	}
}

int main( int argc, char* argv[] )
{
	u32 timerStart;
	u32 timerEnd;
	u32 frameCount = 0;
	SSRE_Vec4_t tri[3];
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	PixelBuffer_t buffer = 
	{
		NULL,
		640,
		480
	};
	u32 shouldQuit = 0;
	buffer.pixels = (u32*)malloc( buffer.w * buffer.h * sizeof( u32 ) );

	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buffer.w, buffer.h, 0 );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, buffer.w, buffer.h );

	timerStart = SDL_GetTicks();
	do
	{
		SDL_Event event;

		if( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_QUIT:
				shouldQuit = 1;
				break;
			default:
				break;
			}
		}

		memset( buffer.pixels, 0x0, sizeof( u32 ) * buffer.w * buffer.h );

		//simpleTestDrawRegioned( pixels, width, height );

		// Setup simple triangle.

		tri[0].x = SSRE_Fixed_FromFloat( 0.0f );
		tri[0].y = SSRE_Fixed_FromFloat( -0.5f );
		tri[0].z = 0;
		tri[0].w = 0;

		tri[1].x = SSRE_Fixed_FromFloat( 0.5f );
		tri[1].y = SSRE_Fixed_FromFloat( 0.5f );
		tri[1].z = 0;
		tri[1].w = 0;

		tri[2].x = SSRE_Fixed_FromFloat( -0.5f );
		tri[2].y = SSRE_Fixed_FromFloat( 0.5f );
		tri[2].z = 0;
		tri[2].w = 0;
		drawTriangle( &buffer, tri, 0xff0000ff );

		SDL_UpdateTexture(texture, NULL, buffer.pixels, buffer.w * sizeof ( u32 ));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		++frameCount;

		if( frameCount == 10 )
		{
			timerEnd = SDL_GetTicks();

			SDL_Log( "10 frames rendered in %u ms (%f ms per frame )\n", timerEnd - timerStart, (float)(timerEnd - timerStart) / 10.0f );

			timerStart = timerEnd;
			frameCount = 0;
		}
	}
	while( !shouldQuit );

	free( buffer.pixels );

	return 0;
}
