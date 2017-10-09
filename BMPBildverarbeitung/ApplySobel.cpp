#include "ApplySobel.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnBlackAndWhite.h"
#include <math.h>

void Filters::ApplySobel(BMP* image)
{

	TurnToGrayScale(*image);
	BMP* tempImage = new BMP(*image);
	
	int width = image->TellWidth();
	int height = image->TellHeight();

	for (int i = 1; i < width - 1; i++) //Iterate through all image pixels without edges
	{
		for (int j = 1; j < height - 1; j++)
		{
			int xPixel = -1 * (*tempImage)(i - 1, j - 1)->Blue + 1 * (*tempImage)(i + 1, j - 1)->Blue
				- 2 * (*tempImage)(i - 1, j)->Blue + 2 * (*tempImage)(i + 1, j)->Blue
				- 1 * (*tempImage)(i - 1, j + 1)->Blue + (*tempImage)(i + 1, j + 1)->Blue;

			int yPixel = -1 * (*tempImage)(i - 1, j - 1)->Blue - 2 * (*tempImage)(i, j - 1)->Blue - 1 * (*tempImage)(i + 1, j - 1)->Blue +
				1 * (*tempImage)(i - 1, j + 1)->Blue + 2 * (*tempImage)(i, j + 1)->Blue + (*tempImage)(i + 1, j + 1)->Blue;

			int grad = std::round(sqrt(yPixel * yPixel + xPixel * xPixel));
			int newValue = grad / 2;
			if (newValue > 255) {
				(*image)(i, j)->Blue = (*image)(i, j)->Green = (*image)(i, j)->Red = 255;
			}
			else {
				(*image)(i, j)->Blue = (*image)(i, j)->Green = (*image)(i, j)->Red = newValue;
			}
		}
	}
	delete tempImage;
}
