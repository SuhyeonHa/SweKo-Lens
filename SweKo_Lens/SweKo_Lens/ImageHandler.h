// ImageHandler.h

#pragma once
#include <iostream>
#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;

class ImageHandler
{
private:
	Mat * image;
	int height;
	int width;
	Vec3b rgb2gray(Vec3b pixel);
	void verticalBlur(Mat * img);
	void horizontalBlur(Mat* img);
	Vec3b averageValue(int x, int y);
public:
	ImageHandler(Mat * image);
	void transform();
	void edgeDetection();
	void countourFinder();
	void displayImage();
	void makeImageGray();
	void gaussianBlur();
	
	~ImageHandler();
};



