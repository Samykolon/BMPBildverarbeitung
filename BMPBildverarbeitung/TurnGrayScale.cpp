#include "TurnGrayScale.h"
#include <iostream>
typedef unsigned char BYTE;

void Filters::TurnToGrayScale(BMP& in)
{
	
	const int width = in.TellWidth();
	const int height = in.TellHeight();

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			double Temp = 0.30*(in(i, j)->Red) +
				0.59*(in(i, j)->Green) +
				0.11*(in(i, j)->Blue);
			in(i, j)->Red = (BYTE)Temp;
			in(i, j)->Green = (BYTE)Temp;
			in(i, j)->Blue = (BYTE)Temp;
		}
	}

	in.SetBitDepth(8);
	
	CreateGrayscaleColorTable(in);
}