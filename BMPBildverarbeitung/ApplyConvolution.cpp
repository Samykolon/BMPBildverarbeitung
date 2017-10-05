#include "ApplyConvolution.h"
#include "EasyBMP.h"
#include "TurnBlackAndWhite.h"

void Filters::ApplyConvolution(const char * filePath, double** convolution, int convHeight)
{
	double conv[3][3] = { { 0.111, 0.111, 0.111 },{ 0.111, 0.111, 0.111 },{ 0.111, 0.111, 0.111 } };
	convHeight = 3;

	BMP Image;
	Image.ReadFromFile("BestesBild.bmp");
	TurnToGrayScale(Image);
	BMP out(Image);

	int edgeGap = (convHeight - 1) / 2; //the width of the edge that is not considered

	for (int i = edgeGap; i < Image.TellWidth() - edgeGap; i++) //Iterate through all image pixels without edges
	{
		for (int j = edgeGap; j < Image.TellHeight() - edgeGap; j++)
		{
			double newPixel = 0;
			for (int a = 0; a < convHeight; a++)
			{
				for (int b = 0; b < convHeight; b++)
				{
					unsigned char currentPixel = Image(i + a - edgeGap, j + b - edgeGap)->Red;
					newPixel += conv[a][b] * currentPixel;
				}
			}
			if (newPixel > 255) {
				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = 255;
			}
			else {
				unsigned char outputpixel = unsigned char(newPixel + 0.5); //round newPixel correctly
				out(i, j)->Blue = out(i, j)->Green = out(i, j)->Red = outputpixel;
			}
		}

	}

	out.WriteToFile("Test.bmp");

}
