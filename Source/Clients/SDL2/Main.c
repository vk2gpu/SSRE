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

int main( int argc, char* argv[] )
{
	SDL_Window* window = NULL;
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

	SSRE_Vec4_t vecC;

	//SSRE_Vec4_Reflect( &vecC, &vecA, &vecB );
	//val = SSRE_Fixed_ToFloat( vecA.x );


	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0 );


	return 0;
}
