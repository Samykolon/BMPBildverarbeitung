#include "ChangeHSVValue.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnGrayScale.h"

void Filters::ChangeHSVValue(BMP& image, double hueFactor, double valueFactor, double saturationFactor)
{
	HSVpixel hsvPixel;
	RGBApixel startPixel;
	const int width = image.TellWidth();
	const int height = image.TellHeight();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			startPixel = image.GetPixel(i, j);
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
			*image(i, j) = finalPixel;

		}
	}
}
