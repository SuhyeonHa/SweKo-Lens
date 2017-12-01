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
	Vec3b averageValue(int x, int y);
	bool verticalEdge(Mat img, int x, int y);
	bool horizontalEdge(Mat img, int x, int y);
	Mat addImages(Mat img1, Mat img2);
public:
	ImageHandler(Mat * image);
	void transform();
	Mat edgeDetection(Mat img);
	Mat sobel(Mat img);
	bool edge(Mat img, int x, int y);
	void countourFinder();
	void displayImage(Mat img);
	void makeImageGray();
	Mat gaussianBlur();
	/* suhyeon*/
	Mat harrisCorner(Mat img);
	void DrawCross(Mat img, int x, int y);
	
	~ImageHandler();
};



