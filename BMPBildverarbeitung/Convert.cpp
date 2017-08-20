#include "Convert.h"

using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;

System::Drawing::Bitmap ^ Convert::ToBitmap(BMP bmp)
{

	return gcnew Bitmap(1, 1);
}

BMP Convert::ToBMP(System::Drawing::Bitmap ^ bitmap)
{
	Rectangle rect = Rectangle(0, 0, bitmap->Width, bitmap->Height);
	BitmapData^ bmpData = bitmap->LockBits(rect, ImageLockMode::ReadOnly, bitmap->PixelFormat);
	System::IntPtr ptr = bmpData->Scan0;
	int bytes = System::Math::Abs(bmpData->Stride) * bitmap->Height;
	array<System::Byte>^ rgbValues = gcnew array<System::Byte>(bytes);
	Marshal::Copy(ptr, rgbValues, 0, bytes);
	bitmap->UnlockBits(bmpData);
	GCHandle handle = GCHandle::Alloc(rgbValues, GCHandleType::Pinned);
	unsigned char* data = (unsigned char*)(void*)handle.AddrOfPinnedObject;	
	//??

	return BMP();
}
