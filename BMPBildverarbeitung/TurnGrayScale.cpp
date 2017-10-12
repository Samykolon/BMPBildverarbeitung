#include "TurnGrayScale.h"
#include <iostream>
#include <emmintrin.h>

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
			in(i, j)->Red = (unsigned char)Temp;
			in(i, j)->Green = (unsigned char)Temp;
			in(i, j)->Blue = (unsigned char)Temp;
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

	//const __m128i singlePixel = _mm_set1_epi32(*(const int*)&pixel2); //Set entire register to pixel2
		
	//for (int i = 0; i < width; i++) { //Iterate through every line because memory is not contiguous
	//	for (RGBApixel* p = in.Pixels[i], *end = &(in.Pixels[i][height]); p < end; p++) { //Iterate through memory directly because it's faster
	//		*p = pixel2;
	//	}
	//}


	const __m128i weigths = _mm_set1_epi64x(0x0000001C0096004C);
	const __m128i zeroes = _mm_setzero_si128();

	for (int i = 0; i < width; i++) { //Iterate through every line because memory of RGBApixel** Pixels is not contiguous
		for (__m128i* p = reinterpret_cast<__m128i*>(in.Pixels[i]), *end = reinterpret_cast<__m128i*>(&(in.Pixels[i][height])); p < end; p++) { //Iterate through memory directly because it's faster
			const __m128i currentPixels = _mm_lddqu_si128(p);
			const __m128i pixelsLow16 = _mm_unpacklo_epi8(currentPixels, zeroes); //unpacked registers contain 2 pixels
			const __m128i pixelsHigh16 = _mm_unpackhi_epi8(currentPixels, zeroes);
			__m128i resultLow16 = _mm_mullo_epi16(pixelsLow16, weigths);
			__m128i resultHigh16 = _mm_mullo_epi16(pixelsHigh16, weigths);
			resultLow16 = _mm_srli_epi16(resultLow16, 8); //Values, with weigths adjusted
			resultHigh16 = _mm_srli_epi16(resultHigh16, 8);
			__m128i grayvalue = _mm_hadd_epi16(resultLow16, resultHigh16);
			grayvalue = _mm_hadd_epi16(grayvalue, zeroes);
			grayvalue = _mm_packus_epi16(grayvalue, grayvalue);
			grayvalue = _mm_unpacklo_epi8(grayvalue, grayvalue);
			grayvalue = _mm_unpacklo_epi8(grayvalue, grayvalue);
			_mm_storeu_si128(p, grayvalue);						
		}
	}
	



}