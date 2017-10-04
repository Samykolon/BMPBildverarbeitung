#include "HSVPixel.h"

RGBApixel HsvToRgb(HsvColor hsv)
{
	RGBApixel rgb;
	unsigned char region, remainder, p, q, t;

	if (hsv.Saturation == 0)
	{
		rgb.Red = hsv.Value;
		rgb.Green = hsv.Value;
		rgb.Blue = hsv.Value;
		rgb.Alpha = 1;
		return rgb;
	}

	region = hsv.Hue / 43;
	remainder = (hsv.Hue - (region * 43)) * 6;

	p = (hsv.Value * (255 - hsv.Saturation)) >> 8;
	q = (hsv.Value * (255 - ((hsv.Saturation * remainder) >> 8))) >> 8;
	t = (hsv.Value * (255 - ((hsv.Saturation * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
	case 0:
		rgb.Red = hsv.Value; rgb.Green = t; rgb.Blue = p;
		break;
	case 1:
		rgb.Red = q; rgb.Green = hsv.Value; rgb.Blue = p;
		break;
	case 2:
		rgb.Red = p; rgb.Green = hsv.Value; rgb.Blue = t;
		break;
	case 3:
		rgb.Red = p; rgb.Green = q; rgb.Blue = hsv.Value;
		break;
	case 4:
		rgb.Red = t; rgb.Green = p; rgb.Blue = hsv.Value;
		break;
	default:
		rgb.Red = hsv.Value; rgb.Green = p; rgb.Blue = q;
		break;
	}

	return rgb;
}

HsvColor RgbToHsv(RGBApixel rgb)
{
	HsvColor hsv;
	unsigned char rgbMin, rgbMax;

	rgbMin = rgb.Red < rgb.Green ? (rgb.Red < rgb.Blue ? rgb.Red : rgb.Blue) : (rgb.Green < rgb.Blue ? rgb.Green : rgb.Blue);
	rgbMax = rgb.Red > rgb.Green ? (rgb.Red > rgb.Blue ? rgb.Red : rgb.Blue) : (rgb.Green > rgb.Blue ? rgb.Green : rgb.Blue);

	hsv.Value = rgbMax;
	if (hsv.Value == 0)
	{
		hsv.Hue = 0;
		hsv.Saturation = 0;
		return hsv;
	}

	hsv.Saturation = 255 * long(rgbMax - rgbMin) / hsv.Value;
	if (hsv.Saturation == 0)
	{
		hsv.Hue = 0;
		return hsv;
	}

	if (rgbMax == rgb.Red)
		hsv.Hue = 0 + 43 * (rgb.Green - rgb.Blue) / (rgbMax - rgbMin);
	else if (rgbMax == rgb.Green)
		hsv.Hue = 85 + 43 * (rgb.Blue - rgb.Red) / (rgbMax - rgbMin);
	else
		hsv.Hue = 171 + 43 * (rgb.Red - rgb.Green) / (rgbMax - rgbMin);

	return hsv;
}
