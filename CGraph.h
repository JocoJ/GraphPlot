#pragma once

#define PADDING 50

#include "CImage.h"

#include "utility.h"

namespace
{
	RGBColor black = { 0, 0, 0 };
	RGBColor white = { 255, 255, 255 };
	RGBColor red = { 255, 0, 0 };
	RGBColor green = { 0, 255, 0 };
	RGBColor blue = { 0, 0 , 255 };
	RGBColor purple = { 255, 0, 255 };
	RGBColor orange = { 255, 255, 0 };
	RGBColor yellor = { 0, 255, 255 };
}

class CGraph
{
	CImage *graph;

	long width, height;
	Interval xAxis, yAxis;
	Point origin;

public:
	CGraph(unsigned int width, unsigned int height, Interval xInterval = Interval(0, 5), Interval yInterval = Interval(0, 5));

	~CGraph();

	void show();
	void write8x8Character(char, int, int);
	void writeString(char*, int, int);

	void plot(int numberOfPoints, double *xVector, double *yVector, RGBColor color = {0, 0, 0});
};

