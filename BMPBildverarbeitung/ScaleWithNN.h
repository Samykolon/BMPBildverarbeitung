#pragma once
#include "EasyBMP.h"

namespace Filters {

	void ScaleWithNN(BMP& image, int newHeight, int newWidth);
	void ScaleWithNNSIMD(BMP &image, int newHeight, int newWidth);

}