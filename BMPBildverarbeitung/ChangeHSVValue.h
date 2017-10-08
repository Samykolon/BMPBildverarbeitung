#pragma once
#include "EasyBMP.h"

namespace Filters {
	void ChangeHSVValue(BMP* Image, double hueFactor, double valueFactor, double saturationFactor);
}