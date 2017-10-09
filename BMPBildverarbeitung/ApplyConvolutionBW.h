#pragma once
#include "EasyBMP.h"
#include "TurnBlackAndWhite.h"

namespace Filters {
	template<size_t rows>
	void ApplyConvolutionBW(BMP* image, double (&convolution)[rows][rows] ) {

		TurnToGrayScale(*image);
		class BMP* tempImage = new BMP(*image);

		
		
		int edgeGap = (rows - 1) / 2; //the width of the edge that is not considered

		const int width = image->TellWidth();
		const int height = image->TellHeight();

		for (int i = edgeGap; i < width - edgeGap; i++) //Iterate through all image pixels without edges
		{
			for (int j = edgeGap; j < height - edgeGap; j++)
			{
				double newPixel = 0;
				for (int a = 0; a < rows; a++)
				{
					for (int b = 0; b < rows; b++)
					{						
						newPixel += convolution[a][b] * (*tempImage)(i + a - edgeGap, j + b - edgeGap)->Red;
					}
				}
				if (newPixel > 255) {
					(*image)(i, j)->Blue = (*image)(i, j)->Green = (*image)(i, j)->Red = 255;
				}
				else {					
					(*image)(i, j)->Blue = (*image)(i, j)->Green = (*image)(i, j)->Red = unsigned char(newPixel + 0.5); //round newPixel correctly
				}
			}

		}
		delete tempImage;
	}
}