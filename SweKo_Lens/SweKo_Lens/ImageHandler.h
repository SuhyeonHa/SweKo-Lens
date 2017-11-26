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
	Vec3b rgb2gray(Vec3b pixel);
public:
	ImageHandler(Mat * image);
	void transform();
	void edgeDetection();
	void countourFinder();
	void displayImage();
	void makeImageGray();
	
	~ImageHandler();
};



