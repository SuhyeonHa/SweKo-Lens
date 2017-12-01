// ImageHandler.cpp

#include "stdafx.h"
#include "ImageHandler.h"
#include <opencv2/core/mat.hpp>
<<<<<<< HEAD

=======
#include <opencv2/highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;



class Point
{
private:
	float x;
	float y;

	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	float getX() { return x; }
	float getY() { return y; }

};
	
ImageHandler::ImageHandler(Mat * img)
{
	this->image = img;
	this->height = image->rows;
	this->width = image->cols;
}
ImageHandler::~ImageHandler()
{
}


Mat transform(Mat img, Point2f points[4])
{
	Point2f tl = points[0];
	Point2f tr = points[1];
	Point2f bl = points[2];
	Point2f br = points[3];

	float widthA = sqrt(pow(br.x - bl.y, 2) + pow(br.x - bl.y, 2));
	float widthB = sqrt(pow(tr.x - tl.x, 2) + pow(tr.y - tl.y, 2));
	int maxWitdh = max(widthA, widthB);

	float heightA = sqrt(pow(tr.x - br.x, 2) + pow(tr.y - br.y, 2));
	float heightB = sqrt(pow(tl.x - bl.x, 2) + pow(tl.y - bl.y, 2));
	int maxheight = max(heightA, heightB);

	Point2f newPoints[4];
	
	newPoints[0] = Point2f(0, 0);
	newPoints[1] = Point2f(maxWitdh - 1, 0);
	newPoints[2] = Point2f(maxWitdh - 1,maxheight - 1);
	newPoints[3] = Point2f(0, maxheight - 1);
	Mat output;
	Mat lambda(2, 4, CV_32FC1);	
	lambda = Mat::zeros(img.rows, img.cols, img.type());
	lambda = getPerspectiveTransform(points, newPoints);
	warpPerspective(img,output, lambda, output.size());
	return output;
}
Mat ImageHandler::edgeDetection(Mat img)
{
	/*int mask[3][3] = {
		{-1, -1, -1},
		{-1 ,8, -1},
		{-1, -1, -1},
	};*/
	int mask1[5][5] = {
		{0,1,1,1,0},
		{1,2,3,2,1},
		{1,3,-32,3,1},
		{1,2,3,2,1},
		{0,1,1,1,0},
	};
	int sum;
	Vec3b color;
	Mat * newImage = new Mat();
	img.copyTo(*newImage);

	for(int y = 3; y < img.rows-3; y++)
	{
		for(int x = 3; x < img.cols-3; x++)
		{
			sum = 0;
			for(int i = 0; i < 5; i++)
			{
				for(int j = 0; j < 5; j++)
				{
					color =	img.at<Vec3b>(cv::Point(x + j - 3, y + i - 3));
					sum += color.val[0] * mask1[i][j];

				}
			}
			sum *= 0.25;
			newImage->at<Vec3b>(cv::Point(x, y)) = Vec3b(sum, sum, sum); 
		}
	}
	return *newImage;
	
}
<<<<<<< HEAD

=======
void ImageHandler::countourFinder()
{
>>>>>>> b063b1ebb42aa991af313721b39a43ed9550fae3

}
void ImageHandler::displayImage(Mat img)
{
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", img);
	
	waitKey(0);
}
Vec3b ImageHandler::rgb2gray(Vec3b pixel)
{
	Vec3b newColor;
	uchar gray;
	uchar blue = pixel.val[0];
	uchar green = pixel.val[1];
	uchar red = pixel.val[2];
	gray = (blue * 2126 + green * 7152 + blue * 722) / 10000;
	newColor.val[0] = gray;
	newColor.val[1] = gray;
	newColor.val[2] = gray;
	return newColor;
}
void ImageHandler::makeImageGray()
{
	Vec3b color;
	
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			color = image->at<Vec3b>(cv::Point(x, y));
			color = rgb2gray(color);
			image->at<Vec3b>(cv::Point(x, y)) = color;
		}
	}
}
Mat ImageHandler::gaussianBlur()
{
	Mat * newImage = new Mat();
	image->copyTo(*newImage);
	Vec3b color;
	for(int y = 2; y < height-3; y++)
	{
		for(int x = 2; x < width-3; x++)
		{
			color = averageValue(x-2, y-2);
			newImage->at<Vec3b>(cv::Point(x, y)) = color;
		}
	}

	return *newImage;
}
Vec3b ImageHandler::averageValue(int x, int y)
{
	float kernel[5][5] = {

		{0.012841,	0.026743,	0.03415,	0.026743,	0.012841},
		{0.026743,	0.055697,	0.071122,	0.055697,	0.026743},
		{0.03415,	0.071122,	0.090818,	0.071122,	0.03415},
		{0.026743,	0.055697,	0.071122,	0.055697,	0.026743},
		{0.012841,	0.026743,	0.03415,	0.026743,	0.012841},
	};
	Vec3b color;
	float blue = 0;
	float green = 0;
	float red = 0;

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			color = image->at<Vec3b>(cv::Point(x+j, y+i));
			blue += color.val[0] * kernel[i][j];
			green += color.val[1] * kernel[i][j];
			red += color.val[2] * kernel[i][j];
		}
	}
	return Vec3b(blue, green, red);
}
Mat ImageHandler::sobel(Mat img)
{
	Mat * imageX = new Mat();
	Mat * imageY = new Mat();
	Mat newImage = Mat();
	img.copyTo(*imageX);
	img.copyTo(*imageY);
	bool check;
	Vec3b white = {255,255,255};
	Vec3b black = { 0,0,0 };
	for(int y = 1; y < img.rows-1; y++)
	{
		for(int x = 1; x < img.cols-1; x++)
		{
			if((check = verticalEdge(img,x,y)) == true)
			{
				
				imageX->at<Vec3b>(cv::Point(x, y)) = black;
			}else
			{
				imageX->at<Vec3b>(cv::Point(x, y)) = white;
			}

			if ((check = horizontalEdge(img, x, y)) == true)
			{
				imageY->at<Vec3b>(cv::Point(x, y)) = black;
			}
			else
			{
				imageY->at<Vec3b>(cv::Point(x, y)) = white;
			}
			
		}
	}
	newImage = addImages(*imageX, *imageY);
	
	return newImage;
}

Mat ImageHandler::addImages(Mat img1, Mat img2)
{
	
	for(int y = 0; y < img1.rows; y++)
	{
		for(int x = 0; x < img1.cols; x++)
		{
			if(img1.at<Vec3b>(cv::Point(x,y)) != img2.at<Vec3b>(cv::Point(x,y)))
			{
				img1.at<Vec3b>(cv::Point(x, y)) = Vec3b(255, 255, 255);
			}
		}
	}

	return img1;
}

bool ImageHandler::verticalEdge(Mat img, int x, int y)
{
	int mask[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1},
	};

	Vec3b color;
	int sum = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			color = img.at<Vec3b>(cv::Point(x + j - 1, y + i - 1));
			sum += color.val[0] * mask[i][j];
		}
	}
	if(sum > -125 && sum  < 125)
	{
		return true;
	}
	return false;
}
bool ImageHandler::horizontalEdge(Mat img, int x, int y)
{
	int mask[3][3] = {
		{ -1, -2, -1 },
		{ 0, 0, 0 },
		{ 1, 2, 1 },
	};

	Vec3b color;
	int sum = 0;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			color = img.at<Vec3b>(cv::Point(x + j - 1, y + i - 1));
			sum += color.val[0] * mask[i][j];
		}
	}
	if (sum > -125 && sum  < 125)
	{
		return true;
	}
	return false;
}

/* suhyeon */
Mat ImageHandler::harrisCorner(Mat img)
{
	int width = img.cols;
	int height = img.rows;

	Mat * newImage = new Mat();
	img.copyTo(*newImage);

	Mat origin; origin = Mat::zeros(height, width, CV_32FC1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)	{
			origin.at<float>(y, x) = img.at<Vec3b>(y, x)[0];
		}
	}

	//imshow("origin", origin);

	Mat imageDxx; imageDxx = Mat::zeros(height, width, CV_32FC1);
	Mat imageDxy; imageDxy = Mat::zeros(height, width, CV_32FC1);
	Mat imageDyy; imageDyy = Mat::zeros(height, width, CV_32FC1); //CV_8UC1

	// 1. CALCULATE (fx)*(fx), (fx)*(fy), (fy)*(fy)
	float dx = 0, dy = 0;

	for (int i = 1; i < height - 2; i++) {
		for (int j = 1; j < width - 2; j++) {
			
			dx = (origin.at<float>(i - 1, j + 1) + origin.at<float>(i, j + 1) + origin.at<float>(i + 1, j + 1)
				- origin.at<float>(i - 1, j - 1) - origin.at<float>(i, j - 1) - origin.at<float>(i + 1, j - 1)) / 6.f;
			dy = (origin.at<float>(i + 1, j - 1) + origin.at<float>(i + 1, j) + origin.at<float>(i + 1, j + 1)
				- origin.at<float>(i - 1, j - 1) - origin.at<float>(i - 1, j) - origin.at<float>(i - 1, j + 1)) / 6.f;
			
			imageDxx.at<float>(i, j) = dx*dx;
			imageDxy.at<float>(i, j) = dx*dy;
			imageDyy.at<float>(i, j) = dy*dy;
		}
	}

	//imshow("dxx", imageDxx);
	//imshow("dxy", imageDxy);
	//imshow("dyy", imageDyy);

	// 2. Gaussian Filtering
	Mat imageGxx; imageGxx = Mat::zeros(height, width, CV_32FC1);
	Mat imageGxy; imageGxy = Mat::zeros(height, width, CV_32FC1);
	Mat imageGyy; imageGyy = Mat::zeros(height, width, CV_32FC1);

	float g[5][5] = { { 1, 4, 6, 4, 1 },{ 4, 16, 24, 16, 4 },
	{ 6, 24, 36, 24, 6 },{ 4, 16, 24, 16, 4 },{ 1, 4, 6, 4, 1 } };

	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
		{
			g[y][x] /= 256.f;
		}

	float gxx, gxy, gyy;
	for (int i = 2; i < height-2; i++)
		for (int j = 2; j < width-2; j++)
		{
			gxx = gyy = gxy = 0;
			for (int y = 0; y < 5; y++)
				for (int x = 0; x < 5; x++)
				{

					gxx += (imageDxx.at<float>(i + y - 2, j + x - 2) * g[y][x]);
					gxy += (imageDxy.at<float>(i + y - 2, j + x - 2) * g[y][x]);
					gyy += (imageDyy.at<float>(i + y - 2, j + x - 2) * g[y][x]);
				}
			//printf("%d %d %d \n", gxx, gxy, gyy);
			imageGxx.at<float>(i,j) = gxx;
			imageGxy.at<float>(i,j) = gxy;
			imageGyy.at<float>(i,j) = gyy;
		}

	//imshow("gxx", imageGxx);
	//imshow("gxy", imageGxy);
	//imshow("gyy", imageGyy);

	//3. Corner Responce Function
	Mat imageCRF; imageCRF = Mat::zeros(height, width, CV_32FC1);
	float val;
	float k = 0.04f;
	for (int i = 0; i < height - 2; i++)
		for (int j = 0; j < width - 2; j++)
		{
			val = (imageGxx.at<float>(i,j) * imageGyy.at<float>(i, j)
				- imageGxy.at<float>(i, j)*imageGxy.at<float>(i, j))
				- k*(imageGxx.at<float>(i, j) + imageGyy.at<float>(i, j))
				*(imageGxx.at<float>(i, j) + imageGyy.at<float>(i, j));
			imageCRF.at<float>(i, j) = val;
			if(val>15000000) printf("%f ", val);
		}
	//imshow("CRF", imageCRF);

	// 4. Decide corner points
	vector<Point2i> corners;
	corners.clear();
	float cvf_value;
	float th = 18000000;//20000000: test.jpg
	int numCount = 0;

	for (int i = 2; i < height - 2; i++)
		for (int j = 2; j < width - 2; j++)
		{
			cvf_value = imageCRF.at<float>(i,j);
			if (cvf_value > th)
			{
				if (cvf_value > imageCRF.at<float>(i - 1, j) && cvf_value > imageCRF.at<float>(i - 1, j + 1) &&
					cvf_value > imageCRF.at<float>(i, j + 1) && cvf_value > imageCRF.at<float>(i + 1, j + 1) &&
					cvf_value > imageCRF.at<float>(i + 1, j) && cvf_value > imageCRF.at<float>(i + 1, j - 1) &&
					cvf_value > imageCRF.at<float>(i, j - 1) && cvf_value > imageCRF.at<float>(i - 1, j - 1))
				{
					numCount++;
					corners.push_back(Point2i(i, j));
					printf("(%d, %d)", i, j);
				}
			}
		}
	printf("%d", numCount);

	// 5. DrowCross
	Mat imageCross; imageCross = Mat::zeros(height, width, CV_32FC1);
	int numCorner = corners.size();
	for (int n = 0; n < numCorner; n++) {
		DrawCross(imageCross, corners.at(n).x, corners.at(n).y);
	}

	//imshow("result", imageCross);

	return imageCross;
}

void ImageHandler::DrawCross(Mat img, int x, int y) {
	printf("%d, %d \n", x, y);
	img.at<float>(x,y) = 255;
	img.at<float>(x, y - 1) = 255;
	img.at<float>(x, y + 1) = 255;
	img.at<float>(x - 1, y) = 255;
	img.at<float>(x + 1, y) = 255;
}





