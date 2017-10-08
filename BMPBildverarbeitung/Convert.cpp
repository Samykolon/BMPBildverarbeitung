#include "Convert.h"

using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;

System::Drawing::Bitmap ^ ConvertBitmap::ToBitmap(BMP *bmp)
{
	System::Drawing::Bitmap ^bitmap = gcnew Bitmap(bmp->TellWidth(), bmp->TellHeight());
	for(int x = 0; x < bmp->TellWidth(); x++)
		for (int y = 0; y < bmp->TellHeight(); y++)
		{
			RGBApixel pixel = bmp->GetPixel(x, y);
			// alpha channel is inverted?
			bitmap->SetPixel(x, y, Color::FromArgb(255 - pixel.Alpha, pixel.Red, pixel.Green, pixel.Blue));
		}
	return bitmap;
}

BMP ConvertBitmap::ToBMP(System::Drawing::Bitmap ^ bitmap) //We might not need this
{
	//Rectangle rect = Rectangle(0, 0, bitmap->Width, bitmap->Height);
	//BitmapData^ bmpData = bitmap->LockBits(rect, ImageLockMode::ReadOnly, bitmap->PixelFormat);
	//System::IntPtr ptr = bmpData->Scan0;
	//int bytes = System::Math::Abs(bmpData->Stride) * bitmap->Height;
	//array<System::Byte>^ rgbValues = gcnew array<System::Byte>(bytes);
	//Marshal::Copy(ptr, rgbValues, 0, bytes);
	//bitmap->UnlockBits(bmpData);
	//GCHandle^ handle = GCHandle::Alloc(rgbValues, GCHandleType::Pinned);
	//unsigned char* data = (unsigned char*)(void*)handle->AddrOfPinnedObject;	
	//??

	return BMP();
}
