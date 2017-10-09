#include "ScaleWithNN.h"
#include "EasyBMP.h"


void Filters::ScaleWithNN(BMP& image, int newHeight, int newWidth)
{

	BMP out;
	out.SetSize(newWidth, newHeight);

	double xMult = newWidth / (double)image.TellWidth();
	double yMult = newHeight / (double)image.TellHeight();


	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{

			*out(i, j) = *image(i / xMult + 0.5, j / yMult + 0.5);

		}
	}
	image.~BMP();
	new(&image) BMP(out);

}
