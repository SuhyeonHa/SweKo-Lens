#include "stdafx.h"
#include "InputHandler.h"
#include "Gui.h"
#include "ImageHandler.h"



int main(int argc, char* argv[])
{
	Mat image;

	InputHandler * input = new InputHandler(argv[1]);
	
	int read_file_check = input->readFile(&image);

	


	//ImageHandler * imageHandler =  new ImageHandler(&image);
	if(read_file_check == -1)
	{
		return -1;
	}
	ImageHandler * image_handler = new ImageHandler(&image);
	image_handler->makeImageGray();
	image_handler->gaussianBlur();
	image_handler->displayImage();
	return 0;
}
