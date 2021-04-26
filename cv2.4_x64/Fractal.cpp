#include "Fractal.h"
#include <Windows.h>
#include <omp.h>

int Fractal::Iteration(Complex a, Complex c)
{
	double maxModulus = 4.0;
	int maxIter = 256;
	int iter = 0;
	
	Complex temp(0,0) ;

	while ( iter < maxIter && a.modulus() < maxModulus)
	{
		a = a * a ;
		a += c;
		iter++;
	}
	return iter;
}

cv::Mat Fractal::generateFractalImage(Border border, CvScalar colortab[256] )
{
	cv::Size size(500,500);

	double xScale = (border.xMax - border.xMin) / size.width;
	double yScale = (border.yMax - border.yMin) / size.height;

	cv::Mat img(size, CV_8UC3);

#pragma omp parallel for schedule(dynamic)
	for (int y=0; y<size.height; y++)
	{
		for (int x=0; x<size.width; x++)
		{
			double cx = border.xMin + x * xScale;
			double cy = border.yMin + y * yScale;

			Complex a(0.0, 0.0);
			Complex c(cx, cy);
			int nIter ;

			if (type == MANDELBROT)
			{
				nIter = Iteration(a, c);
			}
			else if (type == JUALIA)
			{
				nIter = Iteration(c, offset);
			}

			int colorIndex =  (nIter) % 255;

			cv::Vec3b color;
			color.val[0] = colortab[colorIndex].val[0];
			color.val[1] = colortab[colorIndex].val[1];
			color.val[2] = colortab[colorIndex].val[2];
			img.at<cv::Vec3b>(y,x) = color;
		}
	}

	return img;
}
