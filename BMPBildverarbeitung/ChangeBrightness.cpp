#include "ChangeBrightness.h"
#include <iostream>

void Filters::ChangeBrightness(BMP * Image, double factor)
{	
	HSVpixel hsvPixel;
	RGBApixel startPixel;
<<<<<<< HEAD
	const int width = Image.TellWidth();
	const int height = Image.TellHeight();
=======
	const unsigned int width = Image->TellWidth();
	const unsigned int height = Image->TellHeight();
>>>>>>> 06160d8a38db30e12b402a42190f9983fc827af3

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
