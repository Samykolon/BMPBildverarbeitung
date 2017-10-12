#pragma once
#include "EasyBMP.h"

//This is going to be difficult to program and (maybe) a bottleneck
//Another option would be saving it on the hard drive and loading it again,
//which would be much easier to implement, but even slower 
namespace ConvertBitmap {

	System::Drawing::Bitmap^ ToBitmap(BMP *bmp); //Converts an unmanaged BMP to a managed Bitmap
}