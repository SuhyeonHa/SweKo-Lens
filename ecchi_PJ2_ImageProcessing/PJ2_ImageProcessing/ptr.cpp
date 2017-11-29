#pragma once
#include "ptr.h"

using namespace std;
using namespace cv;

ptr::ptr()
{
	pcount = 0;
	for (int i = 0; i < 4; i++)
	{
		p[i].x = 0;
		p[i].y = 0;
	}
}

ptr::ptr(int w, int h)
{
	pcount = 4;
	p[0].x = 0;
	p[0].y = 0;
	p[1].x = w;
	p[1].y = 0;
	p[2].x = 0;
	p[2].y = h;
	p[3].x = w;
	p[3].y = h;
}

void ptr::setp(int x, int y)
{
	if (pcount < 4)
	{
		p[pcount].x = x;
		p[pcount].y = y;
		pcount++;
	}
}

void ptr::reset()
{
	for (int i = 0; i<4; i++)
	{
		p[i].x = 0;
		p[i].y = 0;
	}
	pcount = 0;
}

void ptr::printp()
{
	cout << "pcount: " << pcount << endl;
	cout << "p[0]: " << p[0].x << ", " << p[0].y << endl;
	cout << "p[1]: " << p[1].x << ", " << p[1].y << endl;
	cout << "p[2]: " << p[2].x << ", " << p[2].y << endl;
	cout << "p[3]: " << p[3].x << ", " << p[3].y << endl;
}

bool ptr::isfull()
{
	if (pcount < 4) return false;
	else return true;
}

Point2f* ptr::getp()
{
	return p;
}
