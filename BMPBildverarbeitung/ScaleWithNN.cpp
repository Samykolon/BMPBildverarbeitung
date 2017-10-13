#include "ScaleWithNN.h"
#include "EasyBMP.h"

// Scale with nearest neighbor
void Filters::ScaleWithNN(BMP& image, int newHeight, int newWidth)
{

	BMP out;
	out.SetSize(newWidth, newHeight);

	double xScale = newWidth / (double)image.TellWidth();
	double yScale = newHeight / (double)image.TellHeight();


	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{
			*out(i, j) = *image((int)(i / xScale), (int)(j / yScale));
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

	int newDivisibleWidth = (newWidth / 4) * 4 - 4;

	int newDivisibleHeight = (newHeight / 4) * 4 - 4;

	// Define SIMD to enable SIMD
#define SIMD
#ifndef SIMD
	newDivisibleWidth = 0;
	newDivisibleHeight = 0;
#endif
#undef SIMD

	float xScale = newWidth / (float)image.TellWidth();
	float yScale = newHeight / (float)image.TellHeight();

	// Multiplier vector
	__m128 xScale128 = _mm_set1_ps(xScale);
	__m128 yScale128 = _mm_set1_ps(yScale);

	__m128 counter = _mm_setr_ps(0, 1, 2, 3);

	// Buffer Contains for every position in the new image the position in the old image 
	_int32 *bufferX = new _int32[newWidth];
	_int32 *bufferY = new _int32[newHeight];

	// Generate Lookup for X direction with SIMD instructions
	for (int x = 0; x < newDivisibleWidth; x += 4)
	{
		// 128bit vector with 4 * 32bit x variables initialized
		__m128 coordsX = _mm_set1_ps(x);

		// Add iteration + 0..3
		coordsX = _mm_add_ps(coordsX, counter);

		// position / xscale
		coordsX = _mm_div_ps(coordsX, xScale128);

		// Convert to integer vector
		__m128i coordsXi = _mm_cvttps_epi32(coordsX);

		// Store in buffer
		_mm_storeu_si128((__m128i*)(&bufferX[x]), coordsXi);
	}

	// Iterate through the rest of x
	for (int x = newDivisibleWidth; x < newWidth; x++)
	{
		bufferX[x] = x / xScale;
	}

	// Generate Lookup for Y direction with SIMD instructions
	for (int y = 0; y < newDivisibleHeight; y += 4)
	{
		// 128bit vector with 4 * 32bit x variables initialized
		__m128 coordsY = _mm_set1_ps(y);

		// Add iteration + 0..3
		coordsY = _mm_add_ps(coordsY, counter);

		// position / yscale
		coordsY = _mm_div_ps(coordsY, yScale128);

		// converted to integer vector
		__m128i coordsYi = _mm_cvttps_epi32(coordsY);

		// Store in buffer
		_mm_storeu_si128((__m128i*)(&bufferY[y]), coordsYi);
	}

	// Iterate through the rest of y
	for (int y = newDivisibleHeight; y < newHeight; y++)
	{
		bufferY[y] = y / yScale;
	}

	for (int x = 0; x < newWidth; x++)
	{
		int X = bufferX[x];
		__m128i* store = (__m128i*)(out.Pixels[x]);
		for (int y = 0; y < newDivisibleHeight; y += 4, store++)
		{
			__m128i pixels = _mm_set_epi32(*(__int32*)&image.Pixels[X][bufferY[y + 3]],
				*(__int32*)&image.Pixels[X][bufferY[y + 2]],
				*(__int32*)&image.Pixels[X][bufferY[y + 1]],
				*(__int32*)&image.Pixels[X][bufferY[y]]);
			_mm_storeu_si128(store, pixels);
		}

		for (int y = newDivisibleHeight; y < newHeight; y++)
		{
			out.Pixels[x][y] = image.Pixels[X][bufferY[y]];
		}
	}
	delete[] bufferX;
	delete[] bufferY;

	image.~BMP();
	new(&image) BMP(out);
}