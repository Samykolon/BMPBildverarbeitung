#include "ApplySobel.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnBlackAndWhite.h"
#include <math.h>

void Filters::ApplySobel(const char * filePath)
{
	BMP Image;

	Image.ReadFromFile(filePath);
	TurnToGrayScale(Image);
	BMP out(Image);
	
	const unsigned int width = Image.TellWidth();
	const unsigned int height = Image.TellHeight();

	for (int i = 1; i < width - 1; i++) //Iterate through all image pixels without edges
	{
		for (int j = 1; j < height - 1; j++)
		{
			int xPixel = -1 * Image(i - 1, j - 1)->Blue + 1 * Image(i + 1, j - 1)->Blue
				- 2 * Image(i - 1, j)->Blue + 2 * Image(i + 1, j)->Blue
				- 1 * Image(i - 1, j + 1)->Blue + Image(i + 1, j + 1)->Blue;

			int yPixel = -1 * Image(i - 1, j - 1)->Blue - 2 * Image(i, j - 1)->Blue - 1 * Image(i + 1, j - 1)->Blue +
				1 * Image(i - 1, j + 1)->Blue + 2 * Image(i, j + 1)->Blue + Image(i + 1, j + 1)->Blue;

			int grad = sqrt(yPixel * yPixel + xPixel * xPixel);
			int newValue = grad / 2;
			if (newValue > 255) {
				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = 255;
			}
			else {
				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = newValue;
			}
		}
	}
	out.WriteToFile("Test.bmp");

}
