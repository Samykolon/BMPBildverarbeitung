#pragma once
#include "EasyBMP.h"
#include <string>
#include <fstream>

namespace Filters {
	void TurnToGrayScale(BMP& in);

	void TurnBlackAndWhite(const char* filePath);
}