#include <iostream>
#include "opencv.hpp"
#include "Fractal.h"
#include <Windows.h>


#pragma comment(lib,"opencv_core2410d.lib")                    
#pragma comment(lib,"opencv_highgui2410d.lib")  

cv::Mat img;
Fractal fractal(MANDELBROT);		//mandelbrot set
// 	Complex c(0.1463, -0.315);		//这两行是Julia set
// 	Fractal fractal(JUALIA, c);

//图像大小
cv::Size imageSize(500,500);

//坐标轴范围
Border border = {-2.0, -2.0, 2.0, 2.0};

//颜色
CvScalar colortab[256];
int randomColor[3] = {0,0,0};

//用来记录鼠标按下、弹起
cv::Point pt1(-1, -1);
cv::Point pt2(-1, -1);

//鼠标状态
enum _status{SELECTING, DONE}status = DONE;

void drawSelectRect(cv::Mat img)
{
	cv::Mat temp;
	img.copyTo(temp);
	cv::rectangle(temp, pt1, pt2, CV_RGB(0,255,0), 2); 
	cv::imshow("img", temp);
}


void mouseEventCallback(int event, int x, int y, int flags, void* param)
{
	if( event == CV_EVENT_LBUTTONDOWN)  
	{
		if (x >= 0 && y >= 0 && x < imageSize.width && y < imageSize.height)
		{
			pt1 = cv::Point(x, y);
			status = SELECTING;
		} 
		else
		{
			pt1 = cv::Point(0, 0);
		}
	}
	else if(  event == CV_EVENT_LBUTTONUP)  
	{  
		pt2 = cv::Point(x,y);  
		int dx = abs(pt2.x - pt1.x);  
		int dy = abs(pt2.y - pt1.y);  

		if (x >= 0 && y >= 0 && dx > 5 && dy > 5)  
		{  
			x = min(x, imageSize.width);
			y = min(y, imageSize.height);

			status = DONE;

			double DX = border.xMax - border.xMin;		 
			double DY = border.yMax - border.yMin;

			dx = min(dx, dy);		//使pt1, pt2为正方形，等比显示
			dy = min(dx, dy);
			pt2.x = pt1.x + dx;
			pt2.y = pt1.y + dy;

			double offX = DX / imageSize.width;  
			double offY = DY / imageSize.height;  
			if(pt1.x < pt2.x)  
			{             
				border.xMax = offX * pt2.x + border.xMin;  
				border.xMin = offX * pt1.x + border.xMin;  
			}  
			else  
			{             
				border.xMax = offX * pt1.x + border.xMin;  
				border.xMin = offX * pt2.x + border.xMin;  
			}  
			if(pt1.y < pt2.y)  
			{  
				border.yMax = offY * pt2.y + border.yMin;  
				border.yMin = offY * pt1.y + border.yMin;  
			}  
			else  
			{  
				border.yMax = offY * pt1.y + border.yMin;  
				border.yMin = offY * pt2.y + border.yMin;   
			}  
			DOUBLE TimeStart=GetTickCount();

		

			img = fractal.generateFractalImage(border, colortab);

			DOUBLE TimeEnd=GetTickCount();

			DOUBLE TimeUsed=TimeEnd-TimeStart;
			cout<<" time last:"<<TimeUsed<<endl;
			imshow("img", img);
		}  
	}  
	else if(event == CV_EVENT_RBUTTONDOWN)//右键取消放大，重新选取放大区域  
	{  

	}  
	else if( event == CV_EVENT_MOUSEMOVE && status == SELECTING )//在选取过程中画矩形  
	{  
		pt2 = cv::Point(x,y);  
		double DX = border.xMax - border.xMin;		//接下来转换放大的坐标  
		double DY = border.yMax - border.yMin;

		int dx = abs(pt1.x - pt2.x);
		int dy = abs(pt1.y - pt2.y);
		dx = min(dx, dy);		//使pt1, pt2为正方形，等比显示
		dy = min(dx, dy);
		pt2.x = pt1.x + dx;
		pt2.y = pt1.y + dy;
		
		if(pt1.x > 0 && pt1.y > 0   
			&& pt2.x > 0 && pt2.y > 0  
			&& abs(pt2.x - pt1.x) > 5  
			&& abs(pt2.y - pt1.y) > 5)  
		{  
			drawSelectRect(img);
		}  
	}  
}

void initColor()
{
	for (int i=0; i<256; i++)
	{
		colortab[i].val[0] = (i * 13 + randomColor[0]) % 255;		//配色好看的要领是用小质数
		colortab[i].val[1] = (i * 3 + randomColor[1]) % 255;  
		colortab[i].val[2] = (i * 11 + randomColor[2]) % 255;
	}

}

void main()
{
	initColor();

	cv::namedWindow("img");
	cv::setMouseCallback("img", mouseEventCallback, 0);

	DOUBLE TimeStart=GetTickCount();



	img = fractal.generateFractalImage(border, colortab);

	DOUBLE TimeEnd=GetTickCount();

	DOUBLE TimeUsed=TimeEnd-TimeStart;
	cout<<" time last:"<<TimeUsed<<endl;
	
	imshow("img", img);

	int fileCount = 0;

	/*press "esc" to exit， 
	press 's' to save the image to the current directory,
	press 'r' to reset the image,
	press 'c' to change the color
	*/

	std::cout<<"鼠标左键画框可以放大"<<std::endl;
	std::cout<<" 按 esc 退出"<<std::endl;
	std::cout<<" 按 s 保存当前图像到当前目录"<<std::endl;
	std::cout<<" 按 r 复位"<<std::endl;
	std::cout<<" 按 c 变换颜色"<<std::endl;


	while(1)	
	{
		char key = cv::waitKey(1);
		if (key == 's')
		{
			char pBuf[1000];                                             
			GetCurrentDirectory(1000,pBuf);
			std::string path = pBuf ;
			path += "\\image";

			char file[5];
			itoa(fileCount, file, 10);
			path += file;
			
			path += ".bmp";
			fileCount++;
			cv::imwrite(path, img);
		}
		if (key == 'r')
		{
			border.xMin = -2.0;
			border.yMin = -2.0;
			border.xMax = 2.0;
			border.yMax = 2.0;
			randomColor[0] = 0;
			randomColor[1] = 0;
			randomColor[2] = 0;
			img = fractal.generateFractalImage(border, colortab);
			imshow("img", img);
		}
		if (key == 'c')
		{
			cv::RNG rng(GetTickCount());
			randomColor[0] = rng.uniform(0,256);
			randomColor[1] = rng.uniform(0,256);
			randomColor[2] = rng.uniform(0,256);
			initColor();
			img = fractal.generateFractalImage(border, colortab);
			imshow("img", img);
		}
		if (key == 27)
		{
			break;
		}
	}
	
// 	system("pause");
}