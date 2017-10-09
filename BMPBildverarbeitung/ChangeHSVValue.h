#pragma once
#include "EasyBMP.h"

namespace Filters {
	void ChangeHSVValue(BMP& image, double hueFactor, double valueFactor, double saturationFactor);
}