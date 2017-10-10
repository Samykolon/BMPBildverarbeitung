#pragma once
#include <iostream>
#include <ctime>
#include "EasyBMP.h"
using namespace System::Drawing;


namespace Utilities
{

	class Benchmark
	{
	private:
		std::string name;
		std::clock_t time;

	public:
		Benchmark();

		void StartTimer(std::string str);

		void StopTimer();


	};

	bool compareImage(BMP* image1, BMP* image2);

	System::Drawing::Bitmap^ ToBitmap(BMP *bmp); //Converts an unmanaged BMP to a managed Bitmap

}