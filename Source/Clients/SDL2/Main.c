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

void drawTriangle( PixelBuffer_t* buffer, const void* points, u32 vertexType, u32 vertexStride )
{
	SSRE_Fixed_t y;
	int ret0, ret1;
	int off;
	u32* outPixels;
	SSRE_Vec4_t pixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t pixelBarycentric = { 0, 0, 0, 0 };
	SSRE_Vec4_t halfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t invHalfRes = { 0, 0, 0, 0 };
	SSRE_Vec4_t minCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t minPixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxPixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t edge0, edge1;
	SSRE_Vec4_t line0, line1;
	const SSRE_Vec4_t* point0 = (const SSRE_Vec4_t*)(((char*)points));
	const SSRE_Vec4_t* point1 = (const SSRE_Vec4_t*)(((char*)points) + vertexStride);
	const SSRE_Vec4_t* point2 = (const SSRE_Vec4_t*)(((char*)points) + ( vertexStride << 1 ));
	SSRE_Vec4_t cross20, cross21, cross123;

	// Calculate facing of triangle so we can cull back facing.
	SSRE_Vec4_Sub3( &cross20, point2, point0 );
	SSRE_Vec4_Sub3( &cross21, point1, point0 );
	SSRE_Vec4_Cross2( &cross123, &cross21, &cross20 );
	if( cross123.z > 0 )
	{
		return;
	}
	
	// Setup half res.
	halfRes.x = ( buffer->w << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.y = ( buffer->h << SSRE_FIXED_PRECISION ) >> 1;
	halfRes.z = 1;
	halfRes.w = 1;

	// Setup inv res.
	SSRE_Vec4_Rcp2( &invHalfRes, &halfRes );

	// Find min/max width and height so we don't try to render to the full screen.
	minCoord.x = -SSRE_FIXED_ONE;
	minCoord.y = -SSRE_FIXED_ONE;
	maxCoord.x = SSRE_FIXED_ONE;
	maxCoord.y = SSRE_FIXED_ONE;

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
		line0.x = minCoord.x;
		line0.y = pixel.y;
		line1.x = maxCoord.x;
		line1.y = pixel.y;
		ret0 = SSRE_Math_LineTriangleIntersection2( &edge0, &line0, &line1, point0, point1, point2, SSRE_MATH_INTERSECTION_SEGMENT );
		if( ret0 == SSRE_MATH_INTERSECTION_SEGMENT )
		{
			ret1 = SSRE_Math_LineTriangleIntersection2( &edge1, &line1, &line0, point0, point1, point2, SSRE_MATH_INTERSECTION_SEGMENT );
			if( ret1 == SSRE_MATH_INTERSECTION_SEGMENT )
			{
				if( edge0.x > edge1.x )
				{
					SSRE_Fixed_t temp = edge0.x;
					edge0.x = edge1.x;
					edge1.x = temp;
				}

				off = SSRE_Fixed_Mul( edge0.x, halfRes.x );
				off = off + halfRes.x ;
				off = off >> SSRE_FIXED_PRECISION;
				outPixels = &buffer->pixels[ off + y * buffer->w ];
				for( pixel.x = edge0.x; 
					 pixel.x < edge1.x;  
					 pixel.x += invHalfRes.x, ++outPixels )
				{
					if( ( vertexType & SSRE_VERTEX_HAS_COLOUR ) != 0 )
					{
						SSRE_Math_CartesianToBarycentric33( &pixelBarycentric, point0, point1, point2, &pixel );
			
						// Clamp.
						pixelBarycentric.x = pixelBarycentric.x < SSRE_FIXED_ZERO ? SSRE_FIXED_ZERO : pixelBarycentric.x;
						pixelBarycentric.y = pixelBarycentric.y < SSRE_FIXED_ZERO ? SSRE_FIXED_ZERO : pixelBarycentric.y;
						pixelBarycentric.z = pixelBarycentric.z < SSRE_FIXED_ZERO ? SSRE_FIXED_ZERO : pixelBarycentric.z;
						pixelBarycentric.x = pixelBarycentric.x > SSRE_FIXED_ONE ? SSRE_FIXED_ONE : pixelBarycentric.x;
						pixelBarycentric.y = pixelBarycentric.y > SSRE_FIXED_ONE ? SSRE_FIXED_ONE : pixelBarycentric.y;
						pixelBarycentric.z = pixelBarycentric.z > SSRE_FIXED_ONE ? SSRE_FIXED_ONE : pixelBarycentric.z;
						
						*outPixels = SSRE_Math_LerpColourR8G8B8A8( 3, point0 + 1, vertexStride, &pixelBarycentric.x );
					}
					else
					{
						*outPixels = 0xc0c0c0c0;
					}
				}
			}
		}
	}
}

static SSRE_VertexPCT_t s_CubeVertices[] = 
{
	// Top face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },

	// bottom face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0xff0000ff, 0, 0 },

	// back face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },

	// front face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x00ff00ff, 0, 0 },

	// Right face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },

	// Left face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, 0x0000ffff, 0, 0 },
};

int main( int argc, char* argv[] )
{
	int i;
	u32 timerStart;
	u32 timerEnd;
	u32 frameCount = 0;
	u32 frameTicker = 0;
	const SSRE_VertexPCT_t* firstVertex;

	SSRE_Mat44_t worldMat;
	SSRE_Mat44_t viewMat;
	SSRE_Mat44_t projMat;
	SSRE_Mat44_t ssMat;
	SSRE_Mat44_t clipMat;
	SSRE_MatrixStack_t* matrixStack = SSRE_MatrixStack_Create( 16 );
	SSRE_VertexProcessor_t* vertexProcessor = SSRE_VertexProcessor_Create( 256, SSRE_VERTEX_HAS_POSITION | 
	                                                                            SSRE_VERTEX_HAS_COLOUR |
	                                                                            SSRE_VERTEX_HAS_UV, 
																				sizeof( SSRE_VertexPCT_t ) );
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	PixelBuffer_t buffer = 
	{
		NULL,
		240,
		160
	};
	SSRE_Vec4_t halfRes = 
	{ 
		( buffer.w >> 1 ) << SSRE_FIXED_PRECISION,
		( buffer.h >> 1 ) << SSRE_FIXED_PRECISION,
		0, 
		0 
	};

	u32 shouldQuit = 0;
	buffer.pixels = (u32*)malloc( buffer.w * buffer.h * sizeof( u32 ) );
	SSRE_Mat44_Identity( &worldMat );
	SSRE_Mat44_Identity( &viewMat );
	SSRE_Mat44_Identity( &projMat );
	SSRE_Mat44_Identity( &clipMat );

	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buffer.w * 3, buffer.h * 3, 0 );
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

		// Reset vertex processor.
		SSRE_VertexProcessor_Reset( vertexProcessor );

		// Generate screen space matrix.
		SSRE_Mat44_Identity( &ssMat );
		//ssMat.rows[0].x = halfRes.x;
		//ssMat.rows[1].y = halfRes.y;
		//ssMat.rows[3].x = halfRes.x;
		//ssMat.rows[3].y = halfRes.y;

		// Generate perspective.
		SSRE_Mat44_Perspective( &projMat, 8, SSRE_Fixed_Div( halfRes.y, halfRes.x ), SSRE_Fixed_FromFloat( 1.0f ), SSRE_Fixed_FromFloat( 10.0f ) );

		// Matrices onto stack.
		SSRE_MatrixStack_Push( matrixStack, &ssMat );
		SSRE_MatrixStack_Push( matrixStack, &projMat );
		SSRE_MatrixStack_Push( matrixStack, &viewMat );

		// Draw model.
		{
			SSRE_Mat44_Rotation( &worldMat, frameTicker, frameTicker >> 3, frameTicker >> 6 );
			worldMat.rows[3].x = 0;
			worldMat.rows[3].y = 0;
			worldMat.rows[3].z = -SSRE_FIXED_ONE << 3;

			SSRE_MatrixStack_Push( matrixStack, &worldMat );

			SSRE_MatrixStack_Get( &clipMat, matrixStack );
			firstVertex = (SSRE_VertexPCT_t*)SSRE_VertexProcessor_Process( vertexProcessor, 36, s_CubeVertices, &clipMat );
			for( i = 0; i < 12; ++i )
			{
				drawTriangle( &buffer, firstVertex + ( i * 3 ), vertexProcessor->vertexType, vertexProcessor->vertexStride );
			}

			SSRE_MatrixStack_Pop( matrixStack, 1 );
		}

		// Pop proj and view.
		SSRE_MatrixStack_Pop( matrixStack, 3 );

		SDL_UpdateTexture(texture, NULL, buffer.pixels, buffer.w * sizeof ( u32 ));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		++frameCount;
		frameTicker += 1;
		
		if( frameCount == 60 )
		{
			timerEnd = SDL_GetTicks();

			SDL_Log( "60 frames rendered in %u ms (%f ms per frame )\n", timerEnd - timerStart, (float)(timerEnd - timerStart) / 60.0f );

			timerStart = timerEnd;
			frameCount = 0;
		}
	}
	while( !shouldQuit );

	SSRE_MatrixStack_Destroy( matrixStack );
	SSRE_VertexProcessor_Destroy( vertexProcessor );

	free( buffer.pixels );

	return 0;
}
