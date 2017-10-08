#include "ChangeBrightness.h"
#include <iostream>

void Filters::ChangeBrightness(BMP * image, double factor)
{	
	HSVpixel hsvPixel;
	RGBApixel startPixel;

	const int width = image->TellWidth();
	const int height = image->TellHeight();


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
				
			startPixel = image->GetPixel(i, j);
			hsvPixel = RgbToHsv(startPixel);
			double newValue = hsvPixel.Value * factor;
			if (newValue > 255) {
				hsvPixel.Value = 255;
			}
			else {
				hsvPixel.Value = newValue;
			}
						
			RGBApixel finalPixel = HsvToRgb(hsvPixel);
			*(*image)(i, j) = finalPixel;
		}
	}
}
