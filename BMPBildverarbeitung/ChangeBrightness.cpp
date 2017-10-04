#include "ChangeBrightness.h"
#include <iostream>

void Filters::ChangeBrightness(const char * filePath)
{
	double factor = 0.8;
	BMP Image;
	Image.ReadFromFile(filePath);
	HSVpixel hsvPixel;
	RGBApixel startPixel;
	for (int i = 0; i < Image.TellWidth(); i++) {
		for (int j = 0; j < Image.TellHeight(); j++) {
				
			startPixel = Image.GetPixel(i, j);
			hsvPixel = RgbToHsv(startPixel);
						
			RGBApixel finalPixel = HsvToRgb(hsvPixel);
			*Image(i, j) = finalPixel;
			
		}
	}
	Image.WriteToFile("Test.bmp");

}
