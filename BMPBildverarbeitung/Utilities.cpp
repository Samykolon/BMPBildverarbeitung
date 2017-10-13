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
}