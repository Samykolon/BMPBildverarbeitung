#pragma once
#include "EasyBMP.h"

typedef struct HSVpixel
{
	unsigned char Hue;
	unsigned char Saturation;
	unsigned char Value;
	unsigned char Alpha;
} HSVpixel;

RGBApixel HsvToRgb(HSVpixel hsv);

HSVpixel RgbToHsv(RGBApixel rgb);