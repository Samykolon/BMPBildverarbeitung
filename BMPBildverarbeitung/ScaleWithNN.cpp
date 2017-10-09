#include "ScaleWithNN.h"
#include "EasyBMP.h"


void Filters::ScaleWithNN(BMP* image, int newHeight, int newWidth)
{
	BMP* tempImage = new BMP(*image);
	image->SetSize(newWidth, newHeight);

	double xMult = newWidth / (double)tempImage->TellWidth();
	double yMult = newHeight / (double)tempImage->TellHeight();

	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{
			*(*image)(i, j) = *(*tempImage)(i / xMult + 0.5, j / yMult + 0.5);
		}
	}
	delete tempImage;
}
