#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void diff(Mat&, Mat&, Mat&, Mat&);
void gaussian(Mat&, Mat&);
void corner_response_func(Mat&, Mat&, Mat&, Mat&);
void onMouse(int, int, int, int, void*);
void warp(Mat&, Mat&, Mat&);