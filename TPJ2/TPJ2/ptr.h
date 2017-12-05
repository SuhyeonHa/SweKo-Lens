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
	ptr(int row, int col);
	bool isfull();
	void setp(int x, int y);
	void reset();
	void printp();
	Point2f* getp();
};