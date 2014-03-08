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
#include "SSRE_Mat44.h"

void SSRE_Mat44_Identity( SSRE_Mat44_t* out )
{
	out->rows[0].x = SSRE_FIXED_ONE;  out->rows[0].y = SSRE_FIXED_ZERO; out->rows[0].z = SSRE_FIXED_ZERO; out->rows[0].w = SSRE_FIXED_ZERO;
	out->rows[1].x = SSRE_FIXED_ZERO; out->rows[1].y = SSRE_FIXED_ONE;  out->rows[1].z = SSRE_FIXED_ZERO; out->rows[1].w = SSRE_FIXED_ZERO;
	out->rows[2].x = SSRE_FIXED_ZERO; out->rows[2].y = SSRE_FIXED_ZERO; out->rows[2].z = SSRE_FIXED_ONE;  out->rows[2].w = SSRE_FIXED_ZERO;
	out->rows[3].x = SSRE_FIXED_ZERO; out->rows[3].y = SSRE_FIXED_ZERO; out->rows[3].z = SSRE_FIXED_ZERO; out->rows[3].w = SSRE_FIXED_ONE;
}

void SSRE_Mat44_Rotation( SSRE_Mat44_t* out, int yaw, int pitch, int roll )
{
	SSRE_Fixed_t sy, sp, sr;
	SSRE_Fixed_t cy, cp, cr;

	SSRE_Fixed_t sy_sr;
	SSRE_Fixed_t sy_sp;
	SSRE_Fixed_t sp_sr;
	SSRE_Fixed_t cy_cr;
	SSRE_Fixed_t cy_cp;
	SSRE_Fixed_t cp_cr;

	sy = SSRE_Fixed_Sin( yaw );
	sp = SSRE_Fixed_Sin( pitch );
	sr = SSRE_Fixed_Sin( roll );

	cy = SSRE_Fixed_Cos( yaw );
	cp = SSRE_Fixed_Cos( pitch );
	cr = SSRE_Fixed_Cos( roll );

	sy_sr = SSRE_Fixed_Mul( sy, sr );
	sy_sp = SSRE_Fixed_Mul( sy, sp );
	sp_sr = SSRE_Fixed_Mul( sp, sr );
	cy_cr = SSRE_Fixed_Mul( cy, cr );
	cy_cp = SSRE_Fixed_Mul( cy, cp );
	cp_cr = SSRE_Fixed_Mul( cp, cr );

	out->rows[0].x = cy_cr + SSRE_Fixed_Mul( sy, sp_sr );
	out->rows[0].y = SSRE_Fixed_Mul( -cy, sr ) + SSRE_Fixed_Mul( sy_sp, cr );
	out->rows[0].z = SSRE_Fixed_Mul( sy, cp );
	out->rows[0].w = 0;

	out->rows[1].x = SSRE_Fixed_Mul( sr, cp );
	out->rows[1].y = cp_cr;
	out->rows[1].z = -sp;
	out->rows[1].w = 0;

	out->rows[2].x = SSRE_Fixed_Mul( -sy, cr ) + SSRE_Fixed_Mul( sp_sr, cy );
	out->rows[2].y = sy_sr + SSRE_Fixed_Mul( cy_cr, sp );
	out->rows[2].z = cy_cp;
	out->rows[2].w = 0;

	out->rows[3].x = 0;
	out->rows[3].y = 0;
	out->rows[3].z = 0;
	out->rows[3].w = 1;
}

void SSRE_Mat44_GetColumn( SSRE_Vec4_t* out, const SSRE_Mat44_t* in, int column )
{
	out->x = *(&in->rows[0].x + column);
	out->y = *(&in->rows[1].x + column);
	out->z = *(&in->rows[2].x + column);
	out->w = *(&in->rows[3].x + column);
}

void SSRE_Mat44_Multiply( SSRE_Mat44_t* out, const SSRE_Mat44_t* lhs, const SSRE_Mat44_t* rhs )
{
	SSRE_Vec4_t column;

	assert( out != lhs );
	assert( out != rhs );

	SSRE_Mat44_GetColumn( &column, rhs, 0 );
	out->rows[0].x = SSRE_Vec4_Dot( &column, &lhs->rows[0] );
	out->rows[1].x = SSRE_Vec4_Dot( &column, &lhs->rows[1] );
	out->rows[2].x = SSRE_Vec4_Dot( &column, &lhs->rows[2] );
	out->rows[3].x = SSRE_Vec4_Dot( &column, &lhs->rows[3] );

	SSRE_Mat44_GetColumn( &column, rhs, 1 );
	out->rows[0].y = SSRE_Vec4_Dot( &column, &lhs->rows[0] );
	out->rows[1].y = SSRE_Vec4_Dot( &column, &lhs->rows[1] );
	out->rows[2].y = SSRE_Vec4_Dot( &column, &lhs->rows[2] );
	out->rows[3].y = SSRE_Vec4_Dot( &column, &lhs->rows[3] );

	SSRE_Mat44_GetColumn( &column, rhs, 2 );
	out->rows[0].z = SSRE_Vec4_Dot( &column, &lhs->rows[0] );
	out->rows[1].z = SSRE_Vec4_Dot( &column, &lhs->rows[1] );
	out->rows[2].z = SSRE_Vec4_Dot( &column, &lhs->rows[2] );
	out->rows[3].z = SSRE_Vec4_Dot( &column, &lhs->rows[3] );

	SSRE_Mat44_GetColumn( &column, rhs, 3 );
	out->rows[0].w = SSRE_Vec4_Dot( &column, &lhs->rows[0] );
	out->rows[1].w = SSRE_Vec4_Dot( &column, &lhs->rows[1] );
	out->rows[2].w = SSRE_Vec4_Dot( &column, &lhs->rows[2] );
	out->rows[3].w = SSRE_Vec4_Dot( &column, &lhs->rows[3] );
}