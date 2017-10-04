#pragma once
#include "EasyBMP.h"

typedef struct HSVVpixel
{
	double h;
	double s;
	double v;
	double a;
} HSVVpixel;

RGBApixel Hsv2Rgb(HSVVpixel hsv);

HSVVpixel Rgb2Hsv(RGBApixel rgb);