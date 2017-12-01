// InputHandler.h

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>

using namespace std;
using namespace cv;

class InputHandler
{
private:
	string filename;
public:
	InputHandler(string filename);
	~InputHandler();
	int readFile(Mat* image);
};

