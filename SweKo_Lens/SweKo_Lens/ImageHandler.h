// ImageHandler.h

#pragma once
<<<<<<< HEAD
#include <vector>
=======
#include <iostream>
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class ImageHandler
{
<<<<<<< HEAD
	//friend class P;
	
private:

	Mat image;
=======
private:
	Mat * image;
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3
	int height;
	int width;
	Vec3b rgb2gray(Vec3b pixel);
	Vec3b averageValue(int x, int y);
	bool verticalEdge(Mat img, int x, int y);
	bool horizontalEdge(Mat img, int x, int y);
	Mat addImages(Mat img1, Mat img2);
<<<<<<< HEAD
	

public:
	ImageHandler(Mat image);
	Mat transform(Mat img, Point2f points[4]);
	Mat edgeDetection(Mat img);
	Mat sobel(Mat img);
	//bool edge(Mat img, int x, int y);
=======
public:
	ImageHandler(Mat * image);
	void transform();
	Mat edgeDetection(Mat img);
	Mat sobel(Mat img);
	bool edge(Mat img, int x, int y);
	void countourFinder();
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3
	void displayImage(Mat img);
	void makeImageGray();
	Mat gaussianBlur();
	/* suhyeon*/
	Mat harrisCorner(Mat img);
	void DrawCross(Mat img, int x, int y);
	
<<<<<<< HEAD
=======
	~ImageHandler();
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3
};



