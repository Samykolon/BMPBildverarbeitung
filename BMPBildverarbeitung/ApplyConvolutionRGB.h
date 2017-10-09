#pragma once
#pragma once
#include "EasyBMP.h"

namespace Filters {
	template<size_t rows>
	void ApplyConvolutionRGB(BMP * image, double(&convolution)[rows][rows]) {

		BMP* tempImage = new BMP(*image);

		int edgeGap = (rows - 1) / 2; //the width of the edge that is not considered

		const int width = image->TellWidth();
		const int height = image->TellHeight();

		for (int i = edgeGap; i < width - edgeGap; i++) //Iterate through all image pixels without edges
		{
			for (int j = edgeGap; j < height - edgeGap; j++)
			{
				double newRed = 0;
				double newGreen = 0;
				double newBlue = 0;

				for (int a = 0; a < rows; a++)
				{
					for (int b = 0; b < rows; b++)
					{
						newRed += convolution[a][b] * (*tempImage)(i + a - edgeGap, j + b - edgeGap)->Red;
						newGreen += convolution[a][b] * (*tempImage)(i + a - edgeGap, j + b - edgeGap)->Green;
						newBlue += convolution[a][b] * (*tempImage)(i + a - edgeGap, j + b - edgeGap)->Blue;
					}
				}
				if (newRed > 255) {
					(*image)(i, j)->Red = 255;
				}
				else {					 
					(*image)(i, j)->Red = unsigned char(newRed + 0.5); //round newPixel correctly
				}
				
				if (newGreen > 255) {
					(*image)(i, j)->Green = 255;
				}
				else {
					(*image)(i, j)->Green = unsigned char(newGreen + 0.5); //round newPixel correctly
				}

				if (newBlue > 255) {
					(*image)(i, j)->Blue = 255;
				}
				else {
					(*image)(i, j)->Blue = unsigned char(newBlue + 0.5); //round newPixel correctly
				}
			}

		}

		delete tempImage;
	}
}