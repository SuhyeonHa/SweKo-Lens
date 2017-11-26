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
Vec3b ImageHandler::rgb2gray(Vec3b pixel)
{
	Vec3b newColor;
	uchar gray;
	uchar blue = pixel.val[0];
	uchar green = pixel.val[1];
	uchar red = pixel.val[2];
	gray = (blue * 2126 + green * 7152 + blue * 722) / 10000;
	newColor.val[0] = gray;
	newColor.val[1] = gray;
	newColor.val[2] = gray;
	return newColor;
}
void ImageHandler::makeImageGray()
{
	Vec3b color;
	
	for(int y = 0; y < image->rows; y++)
	{
		for(int x = 0; x < image->cols; x++)
		{
			color = image->at<Vec3b>(cv::Point(x, y));
			color = rgb2gray(color);
			image->at<Vec3b>(cv::Point(x, y)) = color;
		}
	}
}





