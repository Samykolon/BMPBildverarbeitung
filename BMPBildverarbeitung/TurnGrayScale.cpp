#include "TurnGrayScale.h"
#include <iostream>
#include <emmintrin.h>
typedef unsigned char BYTE;

void Filters::TurnToGrayScale(BMP& in)
{

	const int width = in.TellWidth();
	const int height = in.TellHeight();

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			double Temp = 0.30*(in(i, j)->Red) +
				0.59*(in(i, j)->Green) +
				0.11*(in(i, j)->Blue);
			in(i, j)->Red = (BYTE)Temp;
			in(i, j)->Green = (BYTE)Temp;
			in(i, j)->Blue = (BYTE)Temp;
		}
	}
	in.SetBitDepth(8);
	CreateGrayscaleColorTable(in);
}

void Filters::TurnToGrayScaleOptimized(BMP& in)
{

	const int width = in.TellWidth();
	const int height = in.TellHeight();
	
	//for (int i = 0; i < width; i++) { //Iterate through every line because memory is not contiguous
	//	for (RGBApixel* p = in.Pixels[i], *end = &(in.Pixels[i][height - 1]); p < end; p++) { //Iterate through memory directly because it's faster
	//		p->Blue = p->Red = p->Green = p->Alpha = 0;
	//	}
	//}

	//SIMD test
	RGBApixel pixel2;
	pixel2.Red = 111;
	pixel2.Green = 112;
	pixel2.Blue = 113;
	pixel2.Alpha = 114;


	__m128i xmm0 = _mm_cvtsi32_si128(*(const int*)&pixel2); //Load RGBApixel into lower 32 bits of register
	xmm0 = _mm_unpacklo_epi8(xmm0, _mm_setzero_si128());
	xmm0 = _mm_unpacklo_epi16(xmm0, _mm_setzero_si128());




	for (int i = 0; i < width; i++) { //Iterate through every line because memory is not contiguous
		for (RGBApixel* p = in.Pixels[i], *end = &(in.Pixels[i][height - 1]); p < end; p++) { //Iterate through memory directly because it's faster
			p->Blue = p->Red = p->Green = p->Alpha = 0;
		}
	}

	
	
	

}