#include "ScaleWithNN.h"
#include "EasyBMP.h"


void Filters::ScaleWithNN(const char * filePath, int newHeight, int newWidth)
{
	BMP in;
	in.ReadFromFile(filePath);
	BMP out;
	out.SetSize(newWidth, newHeight);

	double xMult = newWidth / (double)in.TellWidth();
	double yMult = newHeight / (double)in.TellHeight();

	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{
			*out(i, j) = *in(i / xMult + 0.5, j / yMult + 0.5);

		}
	}
	out.WriteToFile("ScaleTest.bmp");

}
