#include "CalculateNegative.h"

void Filters::CalculateNegative(BMP & image)
{
	const int width = image.TellWidth();
	const int height = image.TellHeight();

	const __m128i ones = _mm_set1_epi32(0x00FFFFFF);

	for (int i = 0; i < width; i++) { //Iterate through every line because memory of RGBApixel** Pixels is not contiguous
		for (__m128i* p = reinterpret_cast<__m128i*>(image.Pixels[i]), *end = reinterpret_cast<__m128i*>(&(image.Pixels[i][height])); p < end; p++) { //Iterate through memory directly because it's faster
			__m128i currentPixel = _mm_lddqu_si128(p);
			currentPixel = _mm_xor_si128(currentPixel, ones);
			_mm_storeu_si128(p, currentPixel);
		}
	}

}
