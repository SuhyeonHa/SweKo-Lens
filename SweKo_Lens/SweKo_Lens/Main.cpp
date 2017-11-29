#include "stdafx.h"
#include "InputHandler.h"
#include "Gui.h"
#include "ImageHandler.h"



int main(int argc, char* argv[])
{
	Mat image;
	Mat workingImage;
	Mat testImage;
	InputHandler input = InputHandler(argv[1]);
	
	int read_file_check = input.readFile(&image);

	


	//ImageHandler * imageHandler =  new ImageHandler(&image);
	if(read_file_check == -1)
	{
		return -1;
	}

	ImageHandler image_handler = ImageHandler(image);
	image_handler.makeImageGray();
	workingImage = image_handler.gaussianBlur();
	//workingImage = image_handler->edgeDetection(workingImage);
	testImage = image_handler.sobel(workingImage);
	//image_handler.countourFinder(testImage);
	//image_handler.displayImage(testImage);
	return 0;
}
