#include "ApplySobel.h"
#include "EasyBMP.h"
#include "HSVPixel.h"
#include "TurnBlackAndWhite.h"

void Filters::ApplySobel(char * filePath)
{
	BMP Image;
	Image.ReadFromFile(filePath);
	TurnToGrayScale(Image);
	
	float xKernel[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	float yKernel[3][3] = { { -1, -2, -1 },{ 0, 0, 0 },{ 0, 0, 0 } };


	double xMagnitude = 0.0;
	


}
