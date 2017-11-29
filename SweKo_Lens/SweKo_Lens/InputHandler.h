// InputHandler.h

#pragma once
#include "stdafx.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class InputHandler
{
private:
	string filename;
public:
	InputHandler(string filename);
	int readFile(Mat* image);
};

