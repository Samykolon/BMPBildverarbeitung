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

	/*float xKernel[3][3] = { {-1, 0, 1},
							{-2, 0, 2},
							{-1, 0, 1} };


	float yKernel[3][3] = { { -1, -2, -1 },
							{ 0, 0, 0 },
							{ 1, 2, 1 } };

	double xMagnitude = 0.0;*/

	for (int i = 1; i < Image.TellWidth() - 1; i++) //Iterate through all image pixels without edges
	{
		for (int j = 1; j < Image.TellHeight() - 1; j++)
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
