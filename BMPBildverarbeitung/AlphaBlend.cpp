#include "AlphaBlend.h"
#include <emmintrin.h>

void Filters::AlphaBlend(BMP & image, RGBApixel bp)
{

	//Alpha-Blending: The basic formula is result = ((alpha * blendColor) + (255 - alpha) * currentPixelColor)) / 256 
	const int width = image.TellWidth();
	const int height = image.TellHeight();
	int divisibleHeight = (height / 4) * 4;

	const __m128i zeroes = _mm_setzero_si128();
	//Set Alpha value every 16 bits
	const __m128i alpha = _mm_set1_epi16(bp.Alpha); 
	//Calculate (255 - alpha)
	const __m128i alphaComplement = _mm_sub_epi16(_mm_set1_epi16(0x00FF), alpha);
	//Cast it so that it can be read in properly
	__m128i blendColor = _mm_set1_epi32(*reinterpret_cast<unsigned int*>(&bp)); 
	//Create 8-bit gaps full of zeroes between the bp color values, create free space for mullo
	blendColor = _mm_unpacklo_epi8(blendColor, zeroes); 
	//Multiply blendColor by Alpha
	blendColor = _mm_mullo_epi16(blendColor, alpha); 
	//Divide result by 256 (~255)
	blendColor = _mm_srli_epi16(blendColor, 8); 
	//Pack register fully with four times blendPixel 
	blendColor = _mm_packus_epi16(blendColor, blendColor);

	//Iterate through every line because memory of RGBApixel** Pixels is not contiguous
	for (int i = 0; i < width; i++) { 
		__m128i* p = reinterpret_cast<__m128i*>(image.Pixels[i]);
		//Iterate through memory directly because it's faster
		for (int j = 0; j < divisibleHeight; j += 4, p++) { 
			//Load pixels (they are unaligned)
			const __m128i currenPixels = _mm_loadu_si128(p);
			//Unpack Pixels 
			const __m128i currentLow16 = _mm_unpacklo_epi8(currenPixels, zeroes); 
			const __m128i currentHigh16 = _mm_unpackhi_epi8(currenPixels, zeroes);
			//Multiply the color values with alphaComplement
			const __m128i tempLow16 = _mm_mullo_epi16(currentLow16, alphaComplement); 
			const __m128i tempHigh16 = _mm_mullo_epi16(currentHigh16, alphaComplement);
			//Divide value by 256
			const __m128i resultLow16 = _mm_srli_epi16(tempLow16, 8);
			const __m128i resultHigh16 = _mm_srli_epi16(tempHigh16, 8);
			//Pack the resulting colors from 16 bits back to one bit, overflows should not happen (otherwise value is 255)
			const __m128i result = _mm_packus_epi16(resultLow16, resultHigh16); 
			//Store packed result which is an 8-bit sum 
			_mm_storeu_si128(p, _mm_add_epi8(result, blendColor)); 
		}
		//Iterate through the rest of the image that isn't divisible by four
		for (int j = divisibleHeight; j < height; j++) 
		{
			image(i, j)->Red = (bp.Alpha * bp.Red + (255 - bp.Alpha) * image(i, j)->Red) / 256;
			image(i, j)->Green = (bp.Alpha * bp.Green + (255 - bp.Alpha) * image(i, j)->Green) / 256;
			image(i, j)->Blue = (bp.Alpha * bp.Blue + (255 - bp.Alpha) * image(i, j)->Blue) / 256;
		}
	}
}
