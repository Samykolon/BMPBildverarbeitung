#include "ChangeBrightness.h"
#include <iostream>
typedef unsigned char BYTE;

#pragma unmanaged


void Filter::ChangeBrightness(char* fp)
{
	//Copied from EasyBMP example, just a test

	BMP Image;
	Image.ReadFromFile(fp);
	for (int i = 0; i < Image.TellWidth(); i++)
	{
		for (int j = 0; j < Image.TellHeight(); j++)
		{
			double Temp = 0.30*(Image(i, j)->Red) +
				0.59*(Image(i, j)->Green) +
				0.11*(Image(i, j)->Blue);
			Image(i, j)->Red = (BYTE)Temp;
			Image(i, j)->Green = (BYTE)Temp;
			Image(i, j)->Blue = (BYTE)Temp;
		}
	}

	Image.SetBitDepth(8);

	// Create a greyscale color table
	CreateGrayscaleColorTable(Image);

	// write the output file
	Image.WriteToFile("Test.bmp");
}
