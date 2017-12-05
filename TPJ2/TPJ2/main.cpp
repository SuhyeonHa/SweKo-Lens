#include <opencv2/opencv.hpp>
#include <iostream>
#include "ptr.h"
#include "myfunc.h"

using namespace cv;
using namespace std;
void onMouse(int, int, int, int, void*);

ptr psrc = ptr();
ptr pdst;

int main()
{
	Mat src;
	VideoCapture vc;
	//used "IP Webcam" application in smartphone
	//string addr = "http://192.168.219.150:8080/video";// set string "http://ip:8080/video" to connect camera
	string buffaddr = string();
	buffaddr.clear();
	cout << "used IP WebCam Application in smartphone to use webcam" << endl;
	cout << "input webcam's ip address: ";
	cin >> buffaddr;
	string addr = "http://" + buffaddr + ":8080/video";
	if (!vc.open(addr))
	{
		cout << "webcam connect failed" << endl;
		waitKey(0);
		return -1;
	}
	cout << "webcam connected" << endl;
	cout << "your webcam's ip: " + buffaddr + " port: 8080" << endl;
	cout << "press any key to screenshot(except esc key)" << endl;
	cout << "or press esc key to exit" << endl;

	while(waitKey(0)!=27)
	{
		destroyWindow("original");
		destroyWindow("result");
		psrc.reset();
		for (;;)
		{
			if (!vc.read(src))
			{
				cout << "no images" << endl;
				break;
			}
			resize(src, src, Size(500, 500));
			imshow("source", src);
			if (waitKey(1)>=0)
			{
				cout << "capture finished" << endl;
				cout << "click image and set 4 points you want to closeup" << endl;
				cout << "warning: you must click in sequence: top-left, top-right, bottom-left, bottom-right" << endl;
				imshow("original", src);
				break; 
			}
		}
		pdst = ptr(src.rows, src.cols);
		setMouseCallback("original", onMouse, &src);
	}
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
		destroyWindow("result");
		Mat dst((*image).size(), CV_8UC3);
		Mat map;
		cout << "transform" << endl;
		map = calcptm(psrc.getp(), pdst.getp());
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Scalar s = map.at<double>(i, j);
				cout << s(0) << " ";
			}
			cout << endl;
		}
		warp(*image, dst, map);
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