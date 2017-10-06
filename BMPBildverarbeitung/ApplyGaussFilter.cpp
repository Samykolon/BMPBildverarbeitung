#include "ApplyGaussFilterBW.h"
#include "ApplyConvolutionBW.h"

void Filters::ApplyGaussFilterBW(const char * filePath)
{
	double gaussKernel[5][5] = {{0.003765,	0.015019,	0.023792,	0.015019,	0.003765},
								{0.015019,	0.059912,	0.094907,	0.059912,	0.015019},
								{0.023792,	0.094907,	0.150342,	0.094907,	0.023792},
								{0.015019,	0.059912,	0.094907,	0.059912,	0.015019},
								{0.003765,	0.015019,	0.023792,	0.015019,	0.003765}};

	Filters::ApplyConvolutionBW<(size_t) 5>(filePath, gaussKernel);

}
