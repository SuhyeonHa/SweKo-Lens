// ImageHandler.cpp

#include "stdafx.h"
#include "ImageHandler.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

class Point
{
private:
	float x;
	float y;

	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	float getX() { return x; }
	float getY() { return y; }

};
	
ImageHandler::ImageHandler(Mat * img)
{
	this->image = img;
}


ImageHandler::~ImageHandler()
{
}

void ImageHandler::transform()
{

}
void ImageHandler::edgeDetection()
{

}
void ImageHandler::countourFinder()
{

}
void ImageHandler::displayImage()
{
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", *image);

	waitKey(0);
}




