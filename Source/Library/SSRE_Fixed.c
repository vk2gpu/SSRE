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
#include "SSRE_Fixed.h"

static SSRE_Fixed_t s_SineTable[] = 
{
	0x00000000,		// 0
	0x00000647,		// 0.024533
	0x00000c8e,		// 0.049052
	0x000012d3,		// 0.073541
	0x00001915,		// 0.097987
	0x00001f53,		// 0.122373
	0x0000258d,		// 0.146685
	0x00002bc0,		// 0.170909
	0x000031ed,		// 0.195031
	0x00003812,		// 0.219034
	0x00003e2f,		// 0.242906
	0x00004442,		// 0.266632
	0x00004a4a,		// 0.290197
	0x00005047,		// 0.313588
	0x00005637,		// 0.336790
	0x00005c1b,		// 0.359789
	0x000061f0,		// 0.382571
	0x000067b6,		// 0.405123
	0x00006d6c,		// 0.427432
	0x00007311,		// 0.449483
	0x000078a4,		// 0.471263
	0x00007e25,		// 0.492760
	0x00008392,		// 0.513960
	0x000088eb,		// 0.534850
	0x00008e2f,		// 0.555419
	0x0000935e,		// 0.575653
	0x00009875,		// 0.595541
	0x00009d75,		// 0.615070
	0x0000a25c,		// 0.634229
	0x0000a72b,		// 0.653006
	0x0000abe0,		// 0.671390
	0x0000b07a,		// 0.689370
	0x0000b4f9,		// 0.706935
	0x0000b95c,		// 0.724075
	0x0000bda3,		// 0.740778
	0x0000c1cd,		// 0.757035
	0x0000c5d8,		// 0.772837
	0x0000c9c5,		// 0.788174
	0x0000cd93,		// 0.803036
	0x0000d142,		// 0.817414
	0x0000d4d0,		// 0.831301
	0x0000d83d,		// 0.844687
	0x0000db89,		// 0.857565
	0x0000deb3,		// 0.869926
	0x0000e1bb,		// 0.881764
	0x0000e4a0,		// 0.893071
	0x0000e762,		// 0.903840
	0x0000ea00,		// 0.914065
	0x0000ec7a,		// 0.923740
	0x0000eecf,		// 0.932859
	0x0000f100,		// 0.941416
	0x0000f30c,		// 0.949407
	0x0000f4f2,		// 0.956826
	0x0000f6b3,		// 0.963669
	0x0000f84d,		// 0.969931
	0x0000f9c1,		// 0.975610
	0x0000fb0f,		// 0.980702
	0x0000fc36,		// 0.985203
	0x0000fd36,		// 0.989112
	0x0000fe0f,		// 0.992424
	0x0000fec1,		// 0.995140
	0x0000ff4c,		// 0.997256
	0x0000ffaf,		// 0.998772
	0x0000ffeb,		// 0.999687
	0x0000ffff,		// 0.999999
	0x0000ffed,		// 0.999710
	0x0000ffb2,		// 0.998819
	0x0000ff50,		// 0.997327
	0x0000fec7,		// 0.995234
	0x0000fe17,		// 0.992543
	0x0000fd3f,		// 0.989253
	0x0000fc41,		// 0.985369
	0x0000fb1b,		// 0.980891
	0x0000f9cf,		// 0.975822
	0x0000f85c,		// 0.970167
	0x0000f6c3,		// 0.963927
	0x0000f504,		// 0.957106
	0x0000f320,		// 0.949710
	0x0000f116,		// 0.941742
	0x0000eee6,		// 0.933207
	0x0000ec92,		// 0.924110
	0x0000ea19,		// 0.914457
	0x0000e77d,		// 0.904254
	0x0000e4bc,		// 0.893506
	0x0000e1d9,		// 0.882220
	0x0000ded2,		// 0.870403
	0x0000dba9,		// 0.858062
	0x0000d85f,		// 0.845205
	0x0000d4f3,		// 0.831839
	0x0000d166,		// 0.817972
	0x0000cdb9,		// 0.803612
	0x0000c9ec,		// 0.788769
	0x0000c600,		// 0.773451
	0x0000c1f6,		// 0.757667
	0x0000bdce,		// 0.741428
	0x0000b988,		// 0.724742
	0x0000b526,		// 0.707619
	0x0000b0a8,		// 0.690071
	0x0000ac0f,		// 0.672107
	0x0000a75b,		// 0.653739
	0x0000a28d,		// 0.634977
	0x00009da7,		// 0.615833
	0x000098a8,		// 0.596318
	0x00009391,		// 0.576444
	0x00008e64,		// 0.556223
	0x00008921,		// 0.535668
	0x000083c9,		// 0.514789
	0x00007e5c,		// 0.493601
	0x000078dc,		// 0.472116
	0x00007349,		// 0.450347
	0x00006da5,		// 0.428306
	0x000067f0,		// 0.406008
	0x0000622a,		// 0.383465
	0x00005c56,		// 0.360691
	0x00005673,		// 0.337701
	0x00005083,		// 0.314507
	0x00004a87,		// 0.291123
	0x0000447f,		// 0.267565
	0x00003e6c,		// 0.243845
	0x00003850,		// 0.219978
	0x0000322b,		// 0.195979
	0x00002bff,		// 0.171863
	0x000025cb,		// 0.147642
	0x00001f92,		// 0.123333
	0x00001954,		// 0.098949
	0x00001312,		// 0.074506
	0x00000cce,		// 0.050019
	0x00000687,		// 0.025501
	0x0000003f,		// 0.000967
	0xfffff9f8,		// -0.023566
	0xfffff3b1,		// -0.048086
	0xffffed6c,		// -0.072576
	0xffffe72a,		// -0.097024
	0xffffe0ec,		// -0.121412
	0xffffdab2,		// -0.145728
	0xffffd47e,		// -0.169956
	0xffffce51,		// -0.194081
	0xffffc82c,		// -0.218090
	0xffffc20f,		// -0.241968
	0xffffbbfc,		// -0.265699
	0xffffb5f3,		// -0.289271
	0xffffaff5,		// -0.312669
	0xffffaa04,		// -0.335878
	0xffffa421,		// -0.358886
	0xffff9e4b,		// -0.381677
	0xffff9884,		// -0.404238
	0xffff92ce,		// -0.426557
	0xffff8d28,		// -0.448618
	0xffff8794,		// -0.470409
	0xffff8212,		// -0.491917
	0xffff7ca4,		// -0.513129
	0xffff774a,		// -0.534032
	0xffff7205,		// -0.554614
	0xffff6cd6,		// -0.574862
	0xffff67be,		// -0.594763
	0xffff62bd,		// -0.614307
	0xffff5dd5,		// -0.633481
	0xffff5905,		// -0.652273
	0xffff544f,		// -0.670673
	0xffff4fb4,		// -0.688669
	0xffff4b34,		// -0.706250
	0xffff46cf,		// -0.723407
	0xffff4287,		// -0.740128
	0xffff3e5d,		// -0.756403
	0xffff3a50,		// -0.772223
	0xffff3662,		// -0.787578
	0xffff3293,		// -0.802459
	0xffff2ee3,		// -0.816857
	0xffff2b54,		// -0.830763
	0xffff27e5,		// -0.844169
	0xffff2498,		// -0.857067
	0xffff216c,		// -0.869449
	0xffff1e63,		// -0.881307
	0xffff1b7d,		// -0.892635
	0xffff18ba,		// -0.903426
	0xffff161a,		// -0.913672
	0xffff139f,		// -0.923369
	0xffff1147,		// -0.932510
	0xffff0f15,		// -0.941089
	0xffff0d08,		// -0.949102
	0xffff0b20,		// -0.956544
	0xffff095e,		// -0.963410
	0xffff07c2,		// -0.969696
	0xffff064d,		// -0.975398
	0xffff04fe,		// -0.980512
	0xffff03d5,		// -0.985037
	0xffff02d3,		// -0.988969
	0xffff01f9,		// -0.992305
	0xffff0145,		// -0.995044
	0xffff00b9,		// -0.997184
	0xffff0054,		// -0.998723
	0xffff0017,		// -0.999662
	0xffff0001,		// -0.999998
	0xffff0012,		// -0.999733
	0xffff004b,		// -0.998866
	0xffff00ab,		// -0.997397
	0xffff0133,		// -0.995328
	0xffff01e1,		// -0.992660
	0xffff02b8,		// -0.989395
	0xffff03b5,		// -0.985533
	0xffff04d8,		// -0.981079
	0xffff0623,		// -0.976033
	0xffff0794,		// -0.970401
	0xffff092c,		// -0.964184
	0xffff0ae9,		// -0.957386
	0xffff0ccc,		// -0.950013
	0xffff0ed5,		// -0.942067
	0xffff1103,		// -0.933554
	0xffff1356,		// -0.924480
	0xffff15cd,		// -0.914848
	0xffff1868,		// -0.904666
	0xffff1b27,		// -0.893940
	0xffff1e09,		// -0.882675
	0xffff210f,		// -0.870879
	0xffff2436,		// -0.858559
	0xffff277f,		// -0.845722
	0xffff2aea,		// -0.832375
	0xffff2e75,		// -0.818528
	0xffff3221,		// -0.804188
	0xffff35ed,		// -0.789363
	0xffff39d7,		// -0.774064
	0xffff3de1,		// -0.758299
	0xffff4208,		// -0.742077
	0xffff464c,		// -0.725408
	0xffff4aad,		// -0.708303
	0xffff4f2a,		// -0.690771
	0xffff53c2,		// -0.672823
	0xffff5875,		// -0.654471
	0xffff5d42,		// -0.635724
	0xffff6227,		// -0.616595
	0xffff6725,		// -0.597094
	0xffff6c3b,		// -0.577235
	0xffff7167,		// -0.557027
	0xffff76a9,		// -0.536484
	0xffff7c01,		// -0.515619
	0xffff816d,		// -0.494443
	0xffff86ec,		// -0.472969
	0xffff8c7e,		// -0.451210
	0xffff9222,		// -0.429180
	0xffff97d6,		// -0.406892
	0xffff9d9b,		// -0.384359
	0xffffa36f,		// -0.361594
	0xffffa951,		// -0.338611
	0xffffaf41,		// -0.315425
	0xffffb53d,		// -0.292049
	0xffffbb44,		// -0.268497
	0xffffc156,		// -0.244783
	0xffffc772,		// -0.220922
	0xffffcd97,		// -0.196928
	0xffffd3c3,		// -0.172816
	0xffffd9f6,		// -0.148599
	0xffffe02f,		// -0.124293
	0xffffe66d,		// -0.099912
	0xffffecae,		// -0.075471
	0xfffff2f3,		// -0.050985
	0xfffff93a,		// -0.026468
};

SSRE_Fixed_t SSRE_Fixed_Sqrt( SSRE_Fixed_t lhs )
{
	register u64 v = lhs;
	register u64 x = v >> 1;
	register u64 a = 0;

	if( v > 0 && x != 0 )
	{
		do
		{
			a = ( ( v << SSRE_FIXED_DOUBLE_PRECISION ) / x ) >> SSRE_FIXED_PRECISION;
			x = ( ( ( x + a ) << SSRE_FIXED_DOUBLE_PRECISION ) / SSRE_FIXED_TWO ) >> SSRE_FIXED_PRECISION;
		}
		while( ( x * x ) > ( v << SSRE_FIXED_PRECISION ) );

		return (SSRE_Fixed_t)x;
	}

	return 0;
}

SSRE_Fixed_t SSRE_Fixed_Sin( int lhs )
{
	return s_SineTable[ lhs & 0xff ];
}

SSRE_Fixed_t SSRE_Fixed_Cos( int lhs )
{
	return s_SineTable[ ( lhs + 64 ) & 0xff ];
}
