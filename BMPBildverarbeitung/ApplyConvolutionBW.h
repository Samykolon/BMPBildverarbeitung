#pragma once
#include "EasyBMP.h"
#include "TurnBlackAndWhite.h"

namespace Filters {
	template<size_t rows>
	void ApplyConvolutionBW(BMP* Image, double (&convolution)[rows][rows] ) {

		TurnToGrayScale(Image);
		BMP out(Image);

		
		
		int edgeGap = (rows - 1) / 2; //the width of the edge that is not considered

		const int width = Image.TellWidth();
		const int height = Image.TellHeight();

		for (int i = edgeGap; i < width - edgeGap; i++) //Iterate through all image pixels without edges
		{
			for (int j = edgeGap; j < height - edgeGap; j++)
			{
				double newPixel = 0;
				for (int a = 0; a < rows; a++)
				{
					for (int b = 0; b < rows; b++)
					{						
						newPixel += convolution[a][b] * Image(i + a - edgeGap, j + b - edgeGap)->Red;
					}
				}
				if (newPixel > 255) {
					out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = 255;
				}
				else {					
					out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = unsigned char(newPixel + 0.5); //round newPixel correctly
				}
			}

		}
		
		out.WriteToFile("Test.bmp");

	}
}