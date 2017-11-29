#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class ptr
{
private:
	Point2f p[4];
	int pcount;
public:
	ptr();
	ptr(int, int);
	bool isfull();
	void setp(int, int);
	void reset();
	void printp();
	Point2f* getp();
};