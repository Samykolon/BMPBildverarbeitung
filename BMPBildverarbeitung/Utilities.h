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
}