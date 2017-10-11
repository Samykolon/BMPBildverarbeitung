#include "ScaleWithNN.h"
#include "EasyBMP.h"

// Scale with nearest neighbor
void Filters::ScaleWithNN(BMP& image, int newHeight, int newWidth)
{

	BMP out;
	out.SetSize(newWidth, newHeight);

	double xMult = newWidth / (double)image.TellWidth();
	double yMult = newHeight / (double)image.TellHeight();


	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{

			*out(i, j) = *image(i / xMult + 0.5, j / yMult + 0.5);

		}
	}
	image.~BMP();
	new(&image) BMP(out);

}

// Optimized Scale function
void Filters::ScaleWithNNSIMD(BMP &image, int newHeight, int newWidth)
{
	BMP out;
	out.SetSize(newWidth, newHeight);

	int newWidth4 = (newWidth / 4) * 4 - 4;
	
	int newHeight4 = (newHeight / 4) * 4 - 4;
	
	
	// Comment to enable SIMD
	//newWidth4 = 0;
	//newHeight4 = 0;

	double xMult = newWidth / (double)image.TellWidth();
	double yMult = newHeight / (double)image.TellHeight();

	// Multiplier vector
	__m128 xMultiplier = _mm_set1_ps(xMult);
	__m128 yMultiplier = _mm_set1_ps(yMult);

	__m128 counter = _mm_setr_ps(0, 1, 2, 3);
	__m128 halfAdder = _mm_set1_ps(0.5);

	// Buffer Contains for every position in the new image the position in the old image 
	_int32 *bufferX = new _int32[newWidth];
	_int32 *bufferY = new _int32[newHeight];

	// Generate Lookup for X direction with SIMD instructions
	for (int x = 0; x < newWidth4; x += 4)
	{
		// 128bit vector with 4 * 32bit x variables initilized
		__m128 coordsX = _mm_set1_ps(x);

		// Add iteration + 0..3
		coordsX = _mm_add_ps(coordsX, counter);

		// position / multiplier
		coordsX = _mm_div_ps(coordsX, xMultiplier);

		// position + 0.5 and converted to integer vector
		//__m128i coordsXi = _mm_cvtps_epi32(_mm_add_ps(coordsX, halfAdder));
		__m128i coordsXi = _mm_cvtps_epi32(coordsX);

		// Store in buffer
		_mm_storeu_si128((__m128i*)(&bufferX[x]), coordsXi);
	}

	// Iterate through the rest of x
	for (int x = newWidth4; x < newWidth; x++)
	{
		bufferX[x] = x / xMult;
	}

	// Generate Lookup for Y direction with SIMD instructions
	for (int y = 0; y < newHeight4; y += 4)
	{
		// 128bit vector with 4 * 32bit x variables initilized
		__m128 coordsY = _mm_set1_ps(y);

		// Add iteration + 0..3
		coordsY = _mm_add_ps(coordsY, counter);

		// position / multiplier
		coordsY = _mm_div_ps(coordsY, yMultiplier);

		// position + 0.5 and converted to integer vector
		//__m128i coordsYi = _mm_cvtps_epi32(_mm_add_ps(coordsY, halfAdder));
		__m128i coordsYi = _mm_cvtps_epi32(coordsY);

		// Store in buffer
		_mm_storeu_si128((__m128i*)(&bufferY[y]), coordsYi);
	}

	// Iterate through the rest of y
	for (int y = newHeight4; y < newHeight; y++)
	{
		bufferY[y] = y / yMult;
	}

	for (int y = 0; y < newHeight; y++)
	{
		/*
		int Y = bufferY[y];
		for (int x = 0; x < newWidth4; x += 4)
		{
		__m128i pixels = _mm_set_epi32(*(__int32*)&image.Pixels[bufferX[x+0]][Y],
		*(__int32*)&image.Pixels[bufferX[x+1]][Y],
		*(__int32*)&image.Pixels[bufferX[x+2]][Y],
		*(__int32*)&image.Pixels[bufferX[x+3]][Y]);

		__m128i* store = (__m128i*)(&(out.Pixels[x][y]));
		_mm_storeu_si128(store, pixels);
		}
		*/
		for (int x = 0; x < newWidth; x++)
		{
			out.Pixels[x][y] = image.Pixels[bufferX[x]][bufferY[y]];
		}
	}
	delete bufferX;
	delete bufferY;

	image.~BMP();
	new(&image) BMP(out);
}