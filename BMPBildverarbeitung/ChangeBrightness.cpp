#include "ChangeBrightness.h"
#include <iostream>

void Filters::ChangeBrightness(BMP * Image, double factor)
{	
	HSVpixel hsvPixel;
	RGBApixel startPixel;

	const int width = Image->TellWidth();
	const int height = Image->TellHeight();


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
				
			startPixel = Image->GetPixel(i, j);
			hsvPixel = RgbToHsv(startPixel);
			double newValue = hsvPixel.Value * factor;
			if (newValue > 255) {
				hsvPixel.Value = 255;
			}
			else {
				hsvPixel.Value = newValue;
			}
						
			RGBApixel finalPixel = HsvToRgb(hsvPixel);
			*(*Image)(i, j) = finalPixel;
		}
	}
}
