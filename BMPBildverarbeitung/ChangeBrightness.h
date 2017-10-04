#pragma once

#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnBlackAndWhite.h"

namespace Filters {
	void ChangeBrightness(const char* filePath, double factor);
}