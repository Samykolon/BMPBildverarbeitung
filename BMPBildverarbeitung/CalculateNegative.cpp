#include "CalculateNegative.h"

void Filters::CalculateNegative(BMP & image)
{
	const int width = image.TellWidth();
	const int height = image.TellHeight();
	int divisibleHeight = (height / 4) * 4;
	const __m128i ones = _mm_set1_epi32(0x00FFFFFF);

	//Iterate through every line because memory of RGBApixel** Pixels is not contiguous
	for (int i = 0; i < width; i++) { 
		__m128i* p = reinterpret_cast<__m128i*>(image.Pixels[i]);
		for (int j = 0; j < divisibleHeight; j += 4, p++) {
			__m128i currentPixel = _mm_lddqu_si128(p);
			currentPixel = _mm_xor_si128(currentPixel, ones);
			_mm_storeu_si128(p, currentPixel);
		}
		//Iterate through the rest of the image that isn't divisible by four
		for (int j = divisibleHeight; j < height; j++) 
		{
			image(i, j)->Blue = 255 - image(i, j)->Blue;
			image(i, j)->Red = 255 - image(i, j)->Red;
			image(i, j)->Green = 255 - image(i, j)->Green;
		}
	}
}
