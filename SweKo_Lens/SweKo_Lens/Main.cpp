#include "stdafx.h"
#include "InputHandler.h"
#include "Gui.h"
#include "ImageHandler.h"



int main(int argc, char* argv[])
{
	Mat image;
	Mat workingImage;
	InputHandler * input = new InputHandler(argv[1]);
	
	int read_file_check = input->readFile(&image);

	


	//ImageHandler * imageHandler =  new ImageHandler(&image);
	if(read_file_check == -1)
	{
		return -1;
	}
	image.copyTo(workingImage);
	ImageHandler * image_handler = new ImageHandler(&image);
	image_handler->makeImageGray();
	workingImage = image_handler->gaussianBlur();
	workingImage = image_handler->edgeDetection(workingImage);
	image_handler->displayImage(workingImage);
	return 0;
}
