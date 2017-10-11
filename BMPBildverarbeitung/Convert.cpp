#include "Convert.h"
#include <sys/stat.h>

using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;

inline void getTempFileName(std::string &filename)
{
	struct stat buffer;
	do
	{
		filename = std::tmpnam(nullptr);
	} while (stat(filename.c_str(), &buffer) == 0);
}

System::Drawing::Bitmap ^ ConvertBitmap::ToBitmap(BMP *bmp)
{
	std::string tempFile;
	getTempFileName(tempFile);
	// Save BMP to tempFile
	bmp->WriteToFile(tempFile.c_str());
	// Load BMP from tempFile
	System::Drawing::Bitmap ^bitmap = gcnew Bitmap(gcnew System::String(tempFile.c_str()));
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