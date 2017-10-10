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
	

	//SIMD test
	RGBApixel pixel2;
	pixel2.Red = 'r';
	pixel2.Green = 'g';
	pixel2.Blue = 'b';
	pixel2.Alpha = 'a';
				
	const __m128i singlePixel = _mm_set1_epi32(*(const int*)&pixel2); //Set entire register to pixel2
	
	for (int i = 0; i < width; i++) { //Iterate through every line because memory of RGBApixel** Pixels is not contiguous
		for (__m128i* p = reinterpret_cast<__m128i*>(in.Pixels[i]), *end = reinterpret_cast<__m128i*>(&(in.Pixels[i][height])); p < end; p++) { //Iterate through memory directly because it's faster
			_mm_storeu_si128(p, singlePixel); //set all pixels to pixel2, storeu because the pixels are unaligned
		}
	}
	

	//for (int i = 0; i < width; i++) { //Iterate through every line because memory is not contiguous
	//	for (RGBApixel* p = in.Pixels[i], *end = &(in.Pixels[i][height]); p < end; p++) { //Iterate through memory directly because it's faster
	//		*p = pixel2;
	//	}
	//}

	
	
	

}