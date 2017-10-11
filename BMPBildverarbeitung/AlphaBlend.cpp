#include "AlphaBlend.h"
#include <emmintrin.h>

void Filters::AlphaBlend(BMP & image)
{
	const int width = image.TellWidth();
	const int height = image.TellHeight();

	const __m128i zeroes = _mm_setzero_si128();
	const __m128i ones = _mm_set1_epi16(0xFF);
	const __m128i blendColor = _mm_set1_epi32(130);

	//Alpha-Blending: The basic formula is color = ((alpha * color) + (255 - alpha) * blendColor) / 256 

	for (int i = 0; i < width; i++) { //Iterate through every line because memory of RGBApixel** Pixels is not contiguous
		for (__m128i* p = reinterpret_cast<__m128i*>(image.Pixels[i]), *end = reinterpret_cast<__m128i*>(&(image.Pixels[i][height])); p < end; p++) { //Iterate through memory directly because it's faster
			const __m128i currenPixels = _mm_loadu_si128(p);
			const __m128i currentLow16 = _mm_unpacklo_epi8(currenPixels, zeroes); //Unpack Pixels 
			const __m128i currentHigh16 = _mm_unpackhi_epi8(currenPixels, zeroes);
			const __m128i newColor16 = _mm_unpacklo_epi16(blendColor, zeroes);
			__m128i alphaValue = _mm_shufflelo_epi16(newColor16, _MM_SHUFFLE(3, 3, 3, 3)); //Broadcast the top element of the low part of newcolor16 to all four 16-bit areas in the low half of alpha
			alphaValue = _mm_shufflehi_epi16(alphaValue, _MM_SHUFFLE(3, 3, 3, 3)); //Do the same for the high parts of alpha
			const __m128i alphaComplement = _mm_sub_epi16(ones, alphaValue); //Calculate (255 - alphavalue)

		}
	}
}
