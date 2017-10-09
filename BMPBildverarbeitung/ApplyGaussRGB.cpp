#include "ApplyGaussRGB.h"
#include "ApplyConvolutionRGB.h"

void Filters::ApplyGaussFilterRGB(BMP& image)
{
	double gaussKernel[5][5] = { { 0.003765,	0.015019,	0.023792,	0.015019,	0.003765 },
	{ 0.015019,	0.059912,	0.094907,	0.059912,	0.015019 },
	{ 0.023792,	0.094907,	0.150342,	0.094907,	0.023792 },
	{ 0.015019,	0.059912,	0.094907,	0.059912,	0.015019 },
	{ 0.003765,	0.015019,	0.023792,	0.015019,	0.003765 } };

	Filters::ApplyConvolutionRGB<(size_t)5>(image, gaussKernel);	
}
