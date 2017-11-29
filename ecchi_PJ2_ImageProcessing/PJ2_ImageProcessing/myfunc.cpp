#pragma once
#include "myfunc.h"

void diff(Mat& src, Mat& dxx, Mat& dxy, Mat& dyy)
{
	Scalar x, y;
	double _sx[] = { -1.,0.,1.,-2.,0.,2.,-1.,0.,1. };
	double _sy[] = { 1.,2.,1.,0.,0.,0.,-1.,-2.,-1. };
	double threshold = 60.;
	Mat sx = Mat(3, 3, CV_64FC1, _sx);
	Mat sy = Mat(3, 3, CV_64FC1, _sy);
	Mat tx = Mat(3, 3, CV_64FC1);
	Mat ty = Mat(3, 3, CV_64FC1);
	Mat window(3, 3, CV_64FC1);

	for (int w = 1; w < src.rows - 1; w++)
	{
		for (int h = 1; h < src.cols - 1; h++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Scalar s = src.at<uchar>(w - 1 + i, h - 1 + j);
					window.at<double>(i, j) = s(0);
				}
			}
			multiply(window, sx, tx);
			multiply(window, sy, ty);
			x = sum(tx);
			y = sum(ty);
			dxx.at<double>(w, h) = x(0)*x(0) / 32 > threshold ? x(0)*x(0) / 32 : 0.;
			dxy.at<double>(w, h) = x(0)*y(0) / 32 > threshold ? x(0)*y(0) / 32 : 0.;
			dyy.at<double>(w, h) = y(0)*y(0) / 32 > threshold ? y(0)*y(0) / 32 : 0.;
		}
	}
}

void gaussian(Mat& src, Mat& dst)
{
	double __g[] = { 1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, 36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1 };
	Mat _g = Mat(5, 5, CV_64FC1, __g);
	Mat g = Mat(5, 5, CV_64FC1);
	divide(256.0, _g, g);

	Mat window = Mat(5, 5, CV_64FC1);
	Mat temp = Mat(5, 5, CV_64FC1);
	for (int w = 2; w < src.rows - 2; w++)
	{
		for (int h = 2; h < src.cols - 2; h++)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					Scalar s = src.at<double>(w - 2 + i, h - 2 + j);
					window.at<double>(i, j) = s(0);
				}
			}
			multiply(window, g, temp);
			dst.at<double>(w, h) = sum(temp)(0);
		}
	}
}

void corner_response_func(Mat& gdxx, Mat& gdxy, Mat& gdyy, Mat& crf)
{
	double k = 0.04;
	double threshold = 100.;
	for (int w = 2; w < crf.rows - 2; w++)
	{
		for (int h = 2; h < crf.cols - 2; h++)
		{
			Scalar s = (gdxx.at<double>(w, h) * gdyy.at<double>(w, h) - gdxy.at<double>(w, h)*gdxy.at<double>(w, h)) - k*(gdyy.at<double>(w, h) + gdxx.at<double>(w, h))*(gdxx.at<double>(w, h) + gdyy.at<double>(w, h));
			crf.at<double>(w, h) = s(0) > threshold ? s(0) : 0;
		}
	}
}

void warp(Mat& src, Mat& dst, Mat& ptm)
{
	Scalar g = ptm.at<double>(2, 0);
	Scalar h = ptm.at<double>(2, 1);

	Mat inv;
	invert(ptm, inv);
	Scalar ta = inv.at<double>(0, 0);
	Scalar tb = inv.at<double>(0, 1);
	Scalar tc = inv.at<double>(0, 2);
	Scalar td = inv.at<double>(1, 0);
	Scalar te = inv.at<double>(1, 1);
	Scalar tf = inv.at<double>(1, 2);

	double x, y;

	for (int width = 0; width < dst.rows; width++)
	{
		for (int height = 0; height < dst.cols; height++)
		{
			double w = g(0)*width + h(0)*height + 1.;
			x = w*(ta(0)*width + tb(0)*height + tc(0));
			y = w*(td(0)*width + te(0)*height + tf(0));
			dst.at<Vec3b>(width, height) = src.at<Vec3b>((int)x, (int)y);
		}
	}
}