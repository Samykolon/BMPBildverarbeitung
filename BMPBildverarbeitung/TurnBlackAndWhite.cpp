#include "TurnBlackAndWhite.h"
#include <iostream>
typedef unsigned char BYTE;

void Filters::TurnToGrayScale(BMP& in)
{
	
	for (int i = 0; i < in.TellWidth(); i++)
	{
		for (int j = 0; j < in.TellHeight(); j++)
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

void Filters::TurnBlackAndWhite(const char* filePath)
{
	//Copied from EasyBMP example, just a test
	
	BMP Image;
	Image.ReadFromFile(filePath);
	
	TurnToGrayScale(Image);

	// write the output file
	Image.WriteToFile("Test.bmp");
}
