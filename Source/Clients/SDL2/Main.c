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

void testDraw( u32* pixels, int width, int height )
{
	static float ticker = 0.0f;
	int x, y;
	SSRE_Vec4_t pixel;
	SSRE_Vec4_t pixelBarycentric;
	SSRE_Vec4_t halfRes;
	SSRE_Vec4_t tri[3];

	u32 colours[3] = 
	{
		0xffff0000,
		0xff00ff00,
		0xff0000ff,
	};

	// Setup half res.
	halfRes.x = ( width << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.y = ( height << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.z = 1;
	halfRes.w = 1;

	ticker += 0.05f;
	
	// Setup simple triangle.
	tri[0].x = SSRE_Fixed_FromFloat( sinf( ticker ) * 0.5f );
	tri[0].y = SSRE_Fixed_FromFloat( cosf( ticker ) * 0.5f );
	tri[0].z = 0;
	tri[0].w = 0;

	tri[1].x = SSRE_Fixed_FromFloat( 0.5f );
	tri[1].y = SSRE_Fixed_FromFloat( 0.0f );
	tri[1].z = 0;
	tri[1].w = 0;

	tri[2].x = SSRE_Fixed_FromFloat( -0.5f );
	tri[2].y = SSRE_Fixed_FromFloat( 0.0f );
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
		

			SSRE_Math_CartesianToBarycentric3( &pixelBarycentric, tri, &pixel );

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
			else
			{
				*pixels++ = 0x0;
			}
		}
	}	
}


int main( int argc, char* argv[] )
{
	int width = 640;
	int height = 480;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	u32* pixels = (u32*)malloc( width * height * sizeof( u32 ) );
	u32 shouldQuit = 0;
	SSRE_Fixed_t fixedA = SSRE_Fixed_FromFloat( 100.0f );
	SSRE_Fixed_t fixedB = SSRE_Fixed_Sqrt( fixedA );
	float val = 0.0f;
	SSRE_Vec4_t vecA = 
	{
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
	};

	SSRE_Vec4_t vecB = 
	{
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
	};

	//SSRE_Vec4_t vecC;

	//SSRE_Vec4_Reflect( &vecC, &vecA, &vecB );
	//val = SSRE_Fixed_ToFloat( vecA.x );

	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0 );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height );

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

		testDraw( pixels, width, height );

		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof ( u32 ));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	while( !shouldQuit );

	free( pixels );

	return 0;
}
