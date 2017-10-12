#include "DarkenSIMD.h"

void Filters::DarkenSIMD(BMP & image, unsigned char brightness)
{
	//For the brightness: 255 means maintain brightness, everything lower means darken

	const int width = image.TellWidth();
	const int height = image.TellHeight();
	 
	int divisibleHeight = (height / 4) * 4;

	const __m128i brightnessFactor = _mm_set1_epi16(brightness); //set the unsigned char every second byte, 8 bits are always free
	const __m128i zero = _mm_setzero_si128();


	for (int i = 0; i < width; i++) { //Iterate through every line because memory of RGBApixel** Pixels is not contiguous
		__m128i* p = reinterpret_cast<__m128i*>(image.Pixels[i]);
		for (int j = 0; j < divisibleHeight; j += 4, p++) { //Iterate through memory directly because it's faster
			const __m128i loadedPixels = _mm_lddqu_si128(p); //load data from pointer into loadedpixel
			const __m128i loadedLow16 = _mm_unpacklo_epi8(loadedPixels, zero); //interleave each unsigned char for one color (8 bits) with 8 bits full of zeroes
			const __m128i loadedHigh16 = _mm_unpackhi_epi8(loadedPixels, zero); //needed to store result of multiplication
			__m128i resultLow16 = _mm_mullo_epi16(loadedLow16, brightnessFactor); //Mullo because the top 8 bits are zero due to unpacking
			__m128i resultHigh16 = _mm_mullo_epi16(loadedHigh16, brightnessFactor); //16 bit now represent the result of b multiplied by p
			resultLow16 = _mm_srli_epi16(resultLow16, 8); //Result is shifted 8 bits to the left, divided by 256 
			resultHigh16 = _mm_srli_epi16(resultHigh16, 8); //Result is shifted 8 bits to the left, divided by 256 
			_mm_storeu_si128(p, _mm_packus_epi16(resultLow16, resultHigh16)); //Pack back into 8-bit values 
		}
		for (int j = divisibleHeight; j < height; j++) //Iterate through the rest of the image that isn't divisible by four
		{
			image(i, j)->Blue = (int)image(i, j)->Blue * brightness / 256; //256 to optimize
			image(i, j)->Green = (int)image(i, j)->Green * brightness / 256;
			image(i, j)->Red = (int)image(i, j)->Red * brightness / 256;
		}
	}
}
