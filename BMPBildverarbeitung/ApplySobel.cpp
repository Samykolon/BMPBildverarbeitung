#include "ApplySobel.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnGrayScale.h"
#include <math.h>

void Filters::ApplySobel(BMP& image)
{
	
	TurnToGrayScaleOptimized(image);
	BMP out(image);
	int width = image.TellWidth();
	int height = image.TellHeight();

	//Iterate through all image pixels without edges
	for (int i = 1; i < width - 1; i++) 
	{
		for (int j = 1; j < height - 1; j++)
		{
			int xPixel = -1 * image(i - 1, j - 1)->Blue + 1 * image(i + 1, j - 1)->Blue
				- 2 * image(i - 1, j)->Blue + 2 * image(i + 1, j)->Blue
				- 1 * image(i - 1, j + 1)->Blue + image(i + 1, j + 1)->Blue;

			int yPixel = -1 * image(i - 1, j - 1)->Blue - 2 * image(i, j - 1)->Blue - 1 * image(i + 1, j - 1)->Blue +
				1 * image(i - 1, j + 1)->Blue + 2 * image(i, j + 1)->Blue + image(i + 1, j + 1)->Blue;
			
			int grad = std::round(sqrt(yPixel * yPixel + xPixel * xPixel));
			int newValue = grad / 2;
			if (newValue > 255) {

				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = 255;
			}
			else {
				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = newValue;
			}
		}
	}

	image.~BMP(); 
	new(&image) BMP(out);	
	
}
