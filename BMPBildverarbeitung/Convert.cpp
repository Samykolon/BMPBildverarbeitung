#include "Convert.h"
#include <sys/stat.h>
#include <iostream>

using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Windows::Forms;

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
	try {
		System::Drawing::Bitmap ^bitmap = gcnew Bitmap(gcnew System::String(tempFile.c_str()));
		return bitmap;
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Fatal Error (Out Of Memory");
		Application::Exit();
		
	}
		
	
}
