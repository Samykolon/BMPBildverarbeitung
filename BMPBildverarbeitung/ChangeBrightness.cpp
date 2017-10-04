#include "ChangeBrightness.h"
#include <iostream>

void Filters::ChangeBrightness(const char * filePath, double factor)
{	
	BMP Image;
	Image.ReadFromFile(filePath);
	HSVpixel hsvPixel;
	RGBApixel startPixel;
	for (int i = 0; i < Image.TellWidth(); i++) {
		for (int j = 0; j < Image.TellHeight(); j++) {
				
			startPixel = Image.GetPixel(i, j);
			hsvPixel = RgbToHsv(startPixel);
			double newValue = hsvPixel.Value * factor;
			if (newValue > 255) {
				hsvPixel.Value = 255;
			}
			else {
				hsvPixel.Value = newValue;
			}
						
			RGBApixel finalPixel = HsvToRgb(hsvPixel);
			*Image(i, j) = finalPixel;
			
		}
	}
	Image.WriteToFile("Test.bmp");

}
