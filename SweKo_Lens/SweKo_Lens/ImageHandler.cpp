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
	this->height = image->rows;
	this->width = image->cols;
}
ImageHandler::~ImageHandler()
{
}
void ImageHandler::transform()
{

}
Mat ImageHandler::edgeDetection(Mat img)
{
	int mask[3][3] = {
		{-1, -1, -1},
		{-1 ,8, -1},
		{-1, -1, -1},
	};

	int sum;
	Vec3b color;
	Mat * newImage = new Mat();
	img.copyTo(*newImage);

	for(int y = 1; y < img.rows-1; y++)
	{
		for(int x = 1; x < img.cols-1; x++)
		{
			sum = 0;
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					color =	img.at<Vec3b>(cv::Point(x + j - 1, y + i - 1));
					sum += color.val[0] * mask[i][j];

				}
			}
			sum *= 0.07;
			newImage->at<Vec3b>(cv::Point(x, y)) = Vec3b(sum, sum, sum); 
		}
	}
	return *newImage;
	
}
void ImageHandler::countourFinder()
{

}
void ImageHandler::displayImage(Mat img)
{
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", img);
	
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
	
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			color = image->at<Vec3b>(cv::Point(x, y));
			color = rgb2gray(color);
			image->at<Vec3b>(cv::Point(x, y)) = color;
		}
	}
}
Mat ImageHandler::gaussianBlur()
{
	Mat * newImage = new Mat();
	image->copyTo(*newImage);
	Vec3b color;
	for(int y = 2; y < height-3; y++)
	{
		for(int x = 2; x < width-3; x++)
		{
			color = averageValue(x-2, y-2);
			newImage->at<Vec3b>(cv::Point(x, y)) = color;
		}
	}

	return *newImage;
}
Vec3b ImageHandler::averageValue(int x, int y)
{
	float kernel[5][5] = {

		{0.012841,	0.026743,	0.03415,	0.026743,	0.012841},
		{0.026743,	0.055697,	0.071122,	0.055697,	0.026743},
		{0.03415,	0.071122,	0.090818,	0.071122,	0.03415},
		{0.026743,	0.055697,	0.071122,	0.055697,	0.026743},
		{0.012841,	0.026743,	0.03415,	0.026743,	0.012841},
	};
	Vec3b color;
	float blue = 0;
	float green = 0;
	float red = 0;

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			color = image->at<Vec3b>(cv::Point(x+j, y+i));
			blue += color.val[0] * kernel[i][j];
			green += color.val[1] * kernel[i][j];
			red += color.val[2] * kernel[i][j];
		}
	}
	return Vec3b(blue, green, red);
}






