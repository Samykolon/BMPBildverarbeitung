#include "ChangeHSVValue.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "HSVandBack.h"
#include "TurnBlackAndWhite.h"

void Filters::ChangeHSVValue(const char * filePath, double hueFactor, double saturationFactor, double valueFactor)
{
	BMP Image;
	Image.ReadFromFile(filePath);
	
	HSVpixel hsvPixel;
	RGBApixel startPixel;
	for (int i = 0; i < Image.TellWidth(); i++) {
		for (int j = 0; j < Image.TellHeight(); j++) {

			startPixel = Image.GetPixel(i, j);
			hsvPixel = RgbToHsv(startPixel);
			
			double newHue = hsvPixel.Hue * hueFactor;
			if (newHue > 255) {
				hsvPixel.Hue = 255;
			}
			else {
				hsvPixel.Hue = newHue;
			}

			double newSaturation = hsvPixel.Saturation * saturationFactor;
			if (newSaturation > 255) {
				hsvPixel.Saturation = 255;
			}
			else {
				hsvPixel.Saturation = newSaturation;
			}

			double newValue = hsvPixel.Value * valueFactor;
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
