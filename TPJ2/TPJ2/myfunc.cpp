#pragma once
#include "myfunc.h"

void grayscale(Mat& src, Mat& dst)
{
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			Vec3b temp = src.at<Vec3b>(row, col);
			dst.at<uchar>(row, col) = (temp[0] + temp[1] + temp[2]) / 3.;
		}
	}
}

void binarization(Mat& src, Mat& dst)
{
	uchar th, tempth;
	double hist[256] = { 0, };
	double t=0.;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int idx=Scalar(src.at<uchar>(row, col))(0);
			hist[idx]++;
			t += Scalar(src.at<uchar>(row, col))(0);
		}
	}
	t /= src.rows*src.cols;
	tempth = (uchar)t;
	for (int i = 0; i < 256; i++)
	{
		hist[i] /= src.rows*src.cols;
	}
	do
	{
		th = tempth;
		double a1 = 0., b1 = 0., a2=0., b2=0., u1, u2;
		for (int i = 0; i < th; i++)
		{
			a1 += i*hist[i];
			b1 += hist[i];
		}
		if (b1 == 0) b1 = 1.;
		u1 = a1 / b1;
		for (int i = th; i < 256; i++)
		{
			a2 += i*hist[i];
			b2 += hist[i];
		}
		if (b2 == 0) b2 = 1.;
		u2 = a2 / b2;
		tempth = (uchar)((u1 + u2) / 2);
	} while (tempth!=th);

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			uchar temp = src.at<uchar>(row, col);
			dst.at<uchar>(row, col) = temp>th ? 255 : 0;
		}
	}
}

void sobel(Mat& src, Mat& dxx, Mat& dxy, Mat& dyy, Mat& dst)
{
	double _sx[] = { -1., 0., 1., -2., 0., 2., -1., 0., 1. };
	double _sy[] = { 1., 2., 1., 0., 0., 0., -1., -2., -1. };
	double _slr[] = { 0., 1., 2., -1., 0., 1., -2., -1., 0. };
	double _srl[] = { -2., -1., 0., -1., 0., 1., 0., 1., 2. };
	Mat sx(3, 3, CV_64FC1, _sx);
	Mat sy(3, 3, CV_64FC1, _sy);
	Mat slr(3, 3, CV_64FC1, _slr);
	Mat srl(3, 3, CV_64FC1, _srl);
	Mat window(3, 3, CV_64FC1);
	Mat tx(3, 3, CV_64FC1);
	Mat ty(3, 3, CV_64FC1);
	Mat tlr(3, 3, CV_64FC1);
	Mat trl(3, 3, CV_64FC1);
	

	for (int row = 1; row < src.rows - 1; row++)
	{
		for (int col = 1; col < src.cols - 1; col++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Scalar s = src.at<uchar>(row - 1 + i, col - 1 + j);
					window.at<double>(i, j) = s(0);
				}
			}
			multiply(window, sx, tx);
			multiply(window, sy, ty);
			multiply(window, slr, tlr);
			multiply(window, srl, trl);
			Scalar s = (sum(tx)*sum(tx) + sum(ty)*sum(ty));
			Scalar t = (sum(tlr)*sum(tlr) + sum(trl)*sum(trl));
			dxx.at<double>(row, col) = min(sum(tx)(0)*sum(tx)(0), 255.);
			dxy.at<double>(row, col) = min(sum(tx)(0)*sum(ty)(0), 255.);
			dyy.at<double>(row, col) = min(sum(ty)(0)*sum(ty)(0), 255.);
			dst.at<uchar>(row, col) = min(sqrt(s(0) + t(0)), 255.);
		}
	}
	
}

void diff(Mat& src, Mat& dxx, Mat& dxy, Mat& dyy)
{
	Scalar x, y;
	double _sx[] = { -1.,0.,1.,-2.,0.,2.,-1.,0.,1. };
	double _sy[] = { 1.,2.,1.,0.,0.,0.,-1.,-2.,-1. };
	Mat sx = Mat(3, 3, CV_64FC1, _sx);
	Mat sy = Mat(3, 3, CV_64FC1, _sy);
	Mat tx = Mat(3, 3, CV_64FC1);
	Mat ty = Mat(3, 3, CV_64FC1);
	Mat window(3, 3, CV_64FC1);

	for (int row = 1; row < src.rows - 1; row++)
	{
		for (int col = 1; col < src.cols - 1; col++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Scalar s = src.at<uchar>(row - 1 + i, col - 1 + j);
					window.at<double>(i, j) = s(0);
				}
			}
			multiply(window, sx, tx);
			multiply(window, sy, ty);
			x = sum(tx);
			y = sum(ty);
			dxx.at<double>(row, col) = x(0)*x(0);
			dxy.at<double>(row, col) = x(0)*y(0);
			dyy.at<double>(row, col) = y(0)*y(0);
		}
	}
}

void gaussian(Mat& src, Mat& dst)
{
	double __g[] = { 1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, 36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1 };
	Mat _g = Mat(5, 5, CV_64FC1, __g);
	Mat g = Mat(5, 5, CV_64FC1);
	divide(256.0, _g, g);

	Mat window(5, 5, CV_64FC1);	
	Mat temp;
	if (src.type() == CV_64FC1)
	{
		temp = Mat(5, 5, CV_64FC1);
	}
	if (src.type() == CV_8UC1)
	{
		temp = Mat(5, 5, CV_8UC1);
	}
	for (int row = 2; row < src.rows - 2; row++)
	{
		for (int col = 2; col < src.cols - 2; col++)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					Scalar s;
					if (src.type() == CV_64FC1)
					{
						s = src.at<double>(row - 2 + i, col - 2 + j);
					}
					if (src.type() == CV_8UC1)
					{
						s = src.at<uchar>(row - 2 + i, col - 2 + j);
						
					}
					window.at<double>(i, j) = s(0);
				}
			}
			multiply(window, g, temp);
			if(dst.type()==CV_64FC1) dst.at<double>(row, col) = sum(temp)(0);
			if (dst.type() == CV_8UC1) dst.at<uchar>(row, col) = sum(temp)(0);
		}
	}
}

void corner_response_func(Mat& gdxx, Mat& gdxy, Mat& gdyy, Mat& crf)
{
	double k = 0.04;
	double th = 1000000000.;
	for (int row = 2; row < crf.rows - 2; row++)
	{
		for (int col = 2; col < crf.cols - 2; col++)
		{
			Scalar s = (gdxx.at<double>(row, col) * gdyy.at<double>(row, col) - gdxy.at<double>(row, col)*gdxy.at<double>(row, col)) 
				- k*(gdxx.at<double>(row, col) + gdyy.at<double>(row, col))*(gdxx.at<double>(row, col) + gdyy.at<double>(row, col));
			crf.at<double>(row, col) = s(0)>th ? 255 : 0;
			//if (s(0)>th) cout << s(0) << endl;
		}
	}
}

Mat calcptm(Point2f* psrc, Point2f* pdst)
{
	Mat b(8, 1, CV_64FC1);
	Mat x(8, 1, CV_64FC1, Scalar(0));
	Mat a(8, 8, CV_64FC1);
	for (int i = 0; i < 4; i++)
	{
		b.at<double>(i*2, 0) = pdst[i].x;
		b.at<double>(i*2 + 1, 0) = pdst[i].y;
	}

	a.at<double>(0, 0) = psrc[0].x;
	a.at<double>(0, 1) = psrc[0].y;
	a.at<double>(0, 2) = 1.;
	a.at<double>(0, 3) = 0.;
	a.at<double>(0, 4) = 0.;
	a.at<double>(0, 5) = 0.;
	a.at<double>(0, 6) = (-1)*(psrc[0].x*pdst[0].x);
	a.at<double>(0, 7) = (-1)*(psrc[0].y*pdst[0].x);

	a.at<double>(1, 0) = 0.;
	a.at<double>(1, 1) = 0.;
	a.at<double>(1, 2) = 0.;
	a.at<double>(1, 3) = psrc[0].x;
	a.at<double>(1, 4) = psrc[0].y;
	a.at<double>(1, 5) = 1.;
	a.at<double>(1, 6) = (-1)*(psrc[0].x*pdst[0].y);
	a.at<double>(1, 7) = (-1)*(psrc[0].y*pdst[0].y);
	
	a.at<double>(2, 0) = psrc[1].x;
	a.at<double>(2, 1) = psrc[1].y;
	a.at<double>(2, 2) = 1.;
	a.at<double>(2, 3) = 0.;
	a.at<double>(2, 4) = 0.;
	a.at<double>(2, 5) = 0.;
	a.at<double>(2, 6) = (-1)*(psrc[1].x*pdst[1].x);
	a.at<double>(2, 7) = (-1)*(psrc[1].y*pdst[1].x);

	a.at<double>(3, 0) = 0.;
	a.at<double>(3, 1) = 0.;
	a.at<double>(3, 2) = 0.;
	a.at<double>(3, 3) = psrc[1].x;
	a.at<double>(3, 4) = psrc[1].y;
	a.at<double>(3, 5) = 1.;
	a.at<double>(3, 6) = (-1)*(psrc[1].x*pdst[1].y);
	a.at<double>(3, 7) = (-1)*(psrc[1].y*pdst[1].y);

	a.at<double>(4, 0) = psrc[2].x;
	a.at<double>(4, 1) = psrc[2].y;
	a.at<double>(4, 2) = 1.;
	a.at<double>(4, 3) = 0.;
	a.at<double>(4, 4) = 0.;
	a.at<double>(4, 5) = 0.;
	a.at<double>(4, 6) = (-1)*(psrc[2].x*pdst[2].x);
	a.at<double>(4, 7) = (-1)*(psrc[2].y*pdst[2].x);

	a.at<double>(5, 0) = 0.;
	a.at<double>(5, 1) = 0.;
	a.at<double>(5, 2) = 0.;
	a.at<double>(5, 3) = psrc[2].x;
	a.at<double>(5, 4) = psrc[2].y;
	a.at<double>(5, 5) = 1.;
	a.at<double>(5, 6) = (-1)*(psrc[2].x*pdst[2].y);
	a.at<double>(5, 7) = (-1)*(psrc[2].y*pdst[2].y);

	a.at<double>(6, 0) = psrc[3].x;
	a.at<double>(6, 1) = psrc[3].y;
	a.at<double>(6, 2) = 1.;
	a.at<double>(6, 3) = 0.;
	a.at<double>(6, 4) = 0.;
	a.at<double>(6, 5) = 0.;
	a.at<double>(6, 6) = (-1)*(psrc[3].x*pdst[3].x);
	a.at<double>(6, 7) = (-1)*(psrc[3].y*pdst[3].x);

	a.at<double>(7, 0) = 0.;
	a.at<double>(7, 1) = 0.;
	a.at<double>(7, 2) = 0.;
	a.at<double>(7, 3) = psrc[3].x;
	a.at<double>(7, 4) = psrc[3].y;
	a.at<double>(7, 5) = 1.;
	a.at<double>(7, 6) = (-1)*(psrc[3].x*pdst[3].y);
	a.at<double>(7, 7) = (-1)*(psrc[3].y*pdst[3].y);

	solve(a, b, x);
	Mat result = Mat(3, 3, CV_64FC1);
	result.at<double>(0, 0) = x.at<double>(0, 0);
	result.at<double>(0, 1) = x.at<double>(1, 0);
	result.at<double>(0, 2) = x.at<double>(2, 0);
	result.at<double>(1, 0) = x.at<double>(3, 0);
	result.at<double>(1, 1) = x.at<double>(4, 0);
	result.at<double>(1, 2) = x.at<double>(5, 0);
	result.at<double>(2, 0) = x.at<double>(6, 0);
	result.at<double>(2, 1) = x.at<double>(7, 0);
	result.at<double>(2, 2) = 1.;

	return result;
}

void warp(Mat& src, Mat& dst, Mat ptm)
{
	Mat inv=ptm.inv();
	Scalar ta = inv.at<double>(0, 0);
	Scalar tb = inv.at<double>(0, 1);
	Scalar tc = inv.at<double>(0, 2);
	Scalar td = inv.at<double>(1, 0);
	Scalar te = inv.at<double>(1, 1);
	Scalar tf = inv.at<double>(1, 2);
	Scalar tg = inv.at<double>(2, 0);
	Scalar th = inv.at<double>(2, 1);
	Scalar ti = inv.at<double>(2, 2);

	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			double tw = tg(0)*col + th(0)*row + ti(0);
			double w = 1. / tw;
			double x = w*(ta(0)*col + tb(0)*row + tc(0));
			double y = w*(td(0)*col + te(0)*row + tf(0));
			dst.at<Vec3b>(row, col) =src.at<Vec3b>(y, x);
		}
	}
}

Mat houghLines(Mat img, int threshold)
{
	Mat origin = Mat(img.size(), CV_32FC1, Scalar(0));
	int rows = img.rows;
	int cols = img.cols;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			origin.at<float>(row, col) = Scalar(img.at<uchar>(row, col))(0);
		}
	}

	int numRho = (int)(sqrt((double)(rows*rows + cols*cols)) * 2);
	int numTheta = 360;
	
	double* sinLUT = new double[numTheta];
	double* cosLUT = new double[numTheta];

	for (int i = 0; i < numTheta; i++)
	{
		sinLUT[i] = sin(i*PI / numTheta);
		cosLUT[i] = cos(i*PI / numTheta);
	}

	Mat acc = Mat::zeros(numRho, numTheta, CV_32FC1);
	int m;
	
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (origin.at<float>(row, col) == 255)//binary image
			{
				for (int i = 0; i < numTheta; i++)
				{
					m = floor(col*sinLUT[i] + row*cosLUT[i] + 0.5f);
					m += numRho / 2;
					acc.at<float>(m, i)++;
				}
			}
		}
	}
	vector<Point2i> lines;
	lines.clear();
	int temp;

	for (int rho = 1; rho < numRho - 2; rho++)
	{
		for (int theta = 1; theta < numTheta - 2; theta++)
		{
			temp = acc.at<float>(rho, theta);
			if (temp > threshold)
			{
				if (temp > acc.at<float>(rho - 1, theta)
					&& temp > acc.at<float>(rho - 1, theta + 1)
					&& temp > acc.at<float>(rho + 1, theta)
					&& temp > acc.at<float>(rho + 1, theta - 1)
					&& temp > acc.at<float>(rho, theta - 1)
					&& temp > acc.at<float>(rho - 1, theta - 1))
				{
					lines.push_back(Point2i((int)(theta*PI / numTheta), rho - (numRho / 2)));
				}
			}
		}
	}
	Mat result = Mat::zeros(rows, cols, CV_8UC3);
	for (int i = 0; i < lines.size(); i++)
	{
		result.at<Vec3b>(lines.at(i).y, lines.at(i).x)[0] = 255;
	}
	delete[] sinLUT;
	delete[] cosLUT;

	return result;
}

Mat harrisCorner(Mat img)
{
	Mat result=Mat();
	return result;
}