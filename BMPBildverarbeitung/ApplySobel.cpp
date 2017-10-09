#include "ApplySobel.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnGrayScale.h"
#include <math.h>

void Filters::ApplySobel(BMP& image)
{
	TurnToGrayScale(image);
	BMP out(image);
	
	int width = image.TellWidth();
	int height = image.TellHeight();

	for (int i = 1; i < width - 1; i++) //Iterate through all image pixels without edges
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
	image.~BMP(); //Thanks goes out to EasyBMP for not having a copy constructor
	new(&image) BMP(out);	

}
