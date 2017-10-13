#pragma once
#include "EasyBMP.h"


namespace ConvertBitmap {

	System::Drawing::Bitmap^ ToBitmap(BMP *bmp); //Converts an unmanaged BMP to a managed Bitmap
}