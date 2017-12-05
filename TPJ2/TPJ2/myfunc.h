#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#define PI 3.1415926

using namespace std;
using namespace cv;

void grayscale(Mat& src, Mat& dst);
void binarization(Mat& src, Mat& dst);
void diff(Mat& src, Mat& dxx, Mat& dxy, Mat& dyy);
void sobel(Mat& src, Mat& dxx, Mat& dxy, Mat& dyy, Mat& dst);
void gaussian(Mat& src, Mat& dst);
void corner_response_func(Mat& gdxx, Mat& gdxy, Mat& gdyy, Mat& crf);
Mat calcptm(Point2f* psrc, Point2f* pdst);
void warp(Mat& src, Mat& dst, Mat ptm);

Mat houghLines(Mat img, int threshold);
Mat harrisCorner(Mat img);