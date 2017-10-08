#pragma once

#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnBlackAndWhite.h"

namespace Filters {
	void ChangeBrightness(BMP * image, double factor);
}