#include "ApplyGaussFilterBW.h"
#include "ApplyConvolutionBW.h"
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std::chrono;

void Filters::ApplyGaussFilterBW(const char * filePath)
{
	//std::ofstream out("log.txt");
	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	double gaussKernel[5][5] = {{0.003765,	0.015019,	0.023792,	0.015019,	0.003765},
								{0.015019,	0.059912,	0.094907,	0.059912,	0.015019},
								{0.023792,	0.094907,	0.150342,	0.094907,	0.023792},
								{0.015019,	0.059912,	0.094907,	0.059912,	0.015019},
								{0.003765,	0.015019,	0.023792,	0.015019,	0.003765}};

	//Filters::ApplyConvolutionBW<(size_t) 5>(filePath, gaussKernel);
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(t2 - t1).count();

	//out << (std::string)"ApplyGaussFilterBW with " + *filePath + ": " + std::to_string(duration);

	//out.close();
}
