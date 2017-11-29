#include <opencv2/opencv.hpp>
#include <iostream>
#include "ptr.h"
#include "myfunc.h"

using namespace std;
using namespace cv;

ptr psrc = ptr();
ptr pdst;

int main()
{
	Mat src, temp;
	try
	{
		src = imread("C:\\card.jpg", CV_LOAD_IMAGE_COLOR);
		temp = imread("C:\\card.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		if (src.empty()||temp.empty()) throw 0;
	}
	catch (int ex)
	{
		if (ex == NULL)
		{
			cout << "파일 열기 오류" << endl;
			waitKey(0);
			return -1;
		}
	}
	pdst = ptr(src.cols, src.rows);
	//Mat dxx(src.size(), CV_64FC1, Scalar(0));
	//Mat dxy(src.size(), CV_64FC1, Scalar(0));
	//Mat dyy(src.size(), CV_64FC1, Scalar(0));
	//Mat gdxx(src.size(), CV_64FC1, Scalar(0));
	///Mat gdxy(src.size(), CV_64FC1, Scalar(0));
	//Mat gdyy(src.size(), CV_64FC1, Scalar(0));
	//Mat crf(src.size(), CV_64FC1, Scalar(0));
	Mat dst(src.size(), CV_8UC3);
	Mat map;
	//diff(temp, dxx, dxy, dyy);
	//gaussian(dxx, gdxx);
	//gaussian(dxy, gdxy);
	//gaussian(dyy, gdyy);
	//corner_response_func(gdxx, gdxy, gdyy, crf);

	imshow("original", src);
	imshow("result", dst);
	setMouseCallback("original", onMouse, &src);
	//imshow("dxx", dxx);
	//imshow("dxy", dxy);
	//imshow("dyy", dyy);
	//imshow("gdxx", gdxx);
	//imshow("gdxy", gdxy);
	//imshow("gdyy", gdyy);
	//imshow("crf", crf);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

//mouse callback
//left click on original image and store point in structure
//if 4 points stored, calculate perspective transform matrix, warp image, and reset points
void onMouse(int evt, int x, int y, int flag, void* param)
{
	Mat* image = (Mat *)param;
	if (psrc.isfull()) 
	{
		Mat dst((*image).size(), CV_8UC3);
		Mat map;
		cout << "transform" << endl;
		map = getPerspectiveTransform(psrc.getp(), pdst.getp());
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Scalar s = map.at<double>(i, j);
				cout << s(0) << " ";
			}
			cout << endl;
		}
		warpPerspective(*image, dst, map, (*image).size());//in opencv func
		//warp(*image, dst, map);
		imshow("result", dst);
		cout << "reset" << endl;
		psrc.reset();
		~dst;
	}
	else
	{
		switch (evt)
		{
		case CV_EVENT_LBUTTONDOWN:
			psrc.setp(x, y);
			psrc.printp();
			break;
		}
	}
}