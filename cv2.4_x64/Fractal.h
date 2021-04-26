
#include "complex.h"
#include "opencv2/opencv.hpp"

enum FractalType{JUALIA, MANDELBROT};

struct Border 
{
	double xMin;
	double yMin;
	double xMax;
	double yMax;
};

class Fractal
{
private:
	Complex offset;
	FractalType type;

public:
	Fractal(){}
	Fractal(FractalType _type, Complex c = Complex(0,0)) : offset(c), type(_type){}

	cv::Mat generateFractalImage(Border border, CvScalar colortab[256] );
	int Iteration(Complex a, Complex c);

};