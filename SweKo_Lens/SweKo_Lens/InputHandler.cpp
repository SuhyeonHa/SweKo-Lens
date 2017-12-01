// InputHandler.cpp

#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler(string filename)
{
	this->filename = filename;
}


InputHandler::~InputHandler()
{

}

int InputHandler::readFile(Mat * image)
{


	*image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);

	if(!image->data)
	{
		cout << "Could not open file!" << endl;
		return -1;
	}
		
	return 0;
		
}
