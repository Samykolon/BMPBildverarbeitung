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
