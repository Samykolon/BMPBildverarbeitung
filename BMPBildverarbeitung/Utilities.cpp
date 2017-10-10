#include "Utilities.h"
#include <fstream>

namespace Utilities
{
	Benchmark::Benchmark()
	{
		name = "not set";
		time = std::clock();
	}

	void Benchmark::StartTimer(std::string str)
	{
		name = str;
		time = std::clock();
	}

	void Benchmark::StopTimer()
	{
		// current time minus start time
		double duration = (std::clock() - time) / (double)CLOCKS_PER_SEC;
		// Output time in seconds to out.txt
		std::fstream fs;
		fs.open("out.txt", std::fstream::app);
		fs << name.c_str() << ": " << duration << "s" << std::endl;
		fs.close();
	}

	// Returns true if both images are the same otherwise false
	bool compareImage(BMP* image1, BMP* image2)
	{
		// Compare Width and Height
		if (image1->TellHeight() != image2->TellHeight() || image1->TellWidth() != image2->TellWidth())
			return false;

		for (int x = 0; x < image1->TellHeight(); x++)
		{
			for (int y = 0; y < image2->TellWidth(); y++)
			{
				// Compare if both pixels are the same
				if (image1->Pixels[x][y].Alpha != image2->Pixels[x][y].Alpha ||
					image1->Pixels[x][y].Red != image2->Pixels[x][y].Red ||
					image1->Pixels[x][y].Green != image2->Pixels[x][y].Green ||
					image1->Pixels[x][y].Blue != image2->Pixels[x][y].Blue)
					return false;
			}
		}
		return true;
	}
	
	System::Drawing::Bitmap ^ ToBitmap(BMP *bmp)
	{
		System::Drawing::Bitmap ^bitmap = gcnew Bitmap(bmp->TellWidth(), bmp->TellHeight());
		for (int x = 0; x < bmp->TellWidth(); x++)
			for (int y = 0; y < bmp->TellHeight(); y++)
			{
				RGBApixel pixel = bmp->GetPixel(x, y);
				// alpha channel is inverted?
				bitmap->SetPixel(x, y, Color::FromArgb(255 - pixel.Alpha, pixel.Red, pixel.Green, pixel.Blue));
			}
		return bitmap;
	}
}