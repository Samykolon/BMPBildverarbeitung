#include "HSVandBack.h"

RGBApixel Hsv2Rgb(HSVVpixel hsv)
{
	double hh, p, q, t, ff;
	long i;
	RGBApixel rgb;
	rgb.Alpha = hsv.a;

	if (hsv.s <= 0.0)
	{
		rgb.Red = hsv.v;
		rgb.Green = hsv.v;
		rgb.Blue = hsv.v;
		return rgb;
	}

	hh = hsv.h;
	if (hh >= 360.0)
		hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = hsv.v * (1.0 - hsv.s);
	q = hsv.v * (1.0 - (hsv.s * ff));
	t = hsv.v * (1.0 - (hsv.s * (1.0 - ff)));

	switch (i) {

	case 0:
		rgb.Red = hsv.v;
		rgb.Green = t;
		rgb.Blue = p;
		break;
	case 1:
		rgb.Red = q;
		rgb.Green = hsv.v;
		rgb.Blue = p;
		break;
	case 2:
		rgb.Red = p;
		rgb.Green = hsv.v;
		rgb.Blue = t;
		break;
	case 3:
		rgb.Red = p;
		rgb.Green = q;
		rgb.Blue = hsv.v;
		break;
	case 4:
		rgb.Red = t;
		rgb.Green = p;
		rgb.Blue = hsv.v;
		break;
	case 5:
	default:
		rgb.Red = hsv.v;
		rgb.Green = p;
		rgb.Blue = q;
		break;
	}

	return rgb;
}

HSVVpixel Rgb2Hsv(RGBApixel rgb)
{
	HSVVpixel hsv;
	hsv.a = rgb.Alpha;
	double min, max, delta;

	min = rgb.Red < rgb.Green ? rgb.Red : rgb.Green;
	min = min < rgb.Blue ? min : rgb.Blue;

	max = rgb.Red > rgb.Green ? rgb.Red : rgb.Green;
	max = max > rgb.Blue ? max : rgb.Blue;
	
	hsv.v = max;
	delta = max - min;
	if (delta < 0.00001) {

		hsv.s = 0;
		hsv.h = 0; 
		return hsv;
	}
	if (max > 0.0) {
		hsv.s = (delta / max);
	}
	else {
		hsv.s = 0.0;
		hsv.h = NAN;
		return hsv;
	}
	if (rgb.Red >= max)
		hsv.h = (rgb.Green - rgb.Blue) / delta;
	else if (rgb.Green >= max)
		hsv.h = 2.0 + (rgb.Blue - rgb.Red) / delta;
	else
		hsv.h = 4.0 + (rgb.Red - rgb.Green) / delta;

	hsv.h *= 60.0;

	if (hsv.h < 0.0)
		hsv.h += 360.0;

	return hsv;




}
