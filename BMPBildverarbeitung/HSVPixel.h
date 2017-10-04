#pragma once
#include "EasyBMP.h"

typedef struct HsvColor
{
	unsigned char Hue;
	unsigned char Saturation;
	unsigned char Value;
} HsvColor;

RGBApixel HsvToRgb(HsvColor hsv);

HsvColor RgbToHsv(RGBApixel rgb);