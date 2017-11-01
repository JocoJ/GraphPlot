#include <exception>
#include <Windows.h>
#include <iostream>
#include "characters.h"
#include "CGraph.h"

CGraph::CGraph(unsigned int width, unsigned int height, Interval x, Interval y) : xAxis(x), yAxis(y)
{
	if (width > PADDING && height > PADDING)
	{
		graph = new CImage(width, height);
		this->width = width;
		this->height = height;

		origin.x = width * fabs(x.left) / (x.length()) + PADDING;
		origin.y = height * fabs(y.left) / (y.length());

		for (unsigned int i = PADDING; i < this->height-PADDING; ++i)
		{
			graph->putPixel(black, i, origin.x);
		}
		for (unsigned int i = PADDING; i < width - PADDING; ++i)
		{
			graph->putPixel(black, origin.y, i);
		}
		write8x8Character('0', origin.x-10, origin.y - 10);
	}
	else
	{
		throw new std::exception("Invalid size");
	}
}

CGraph::~CGraph()
{
	delete graph;
}

void CGraph::show()
{
	graph->writeImage("temp.bmp");
	HINSTANCE x = ShellExecute(0, 0, L"temp.bmp", 0, 0, SW_SHOW);
	std::cout << x <<'\n';
}

void CGraph::write8x8Character(char c, int x_coord, int y_coord)
{
	int val = c - '0';
	if (val >= 0 && val <= 9)
	{
		for (int i = 0, k = y_coord+8; i < 64; k--)
		{
			for (int j = 0; j < 8; j++, i++)
			{
				RGBColor color = (Digits[val][i] == 1) ?  black : white;
				this->graph->putPixel(color,  k, x_coord + j);
			}
		}
	}
}

void CGraph::writeString(char *string, int x_coord, int y_coord)
{
	for (int i = 0; string[i]; ++i)
	{
		write8x8Character(string[i], x_coord + i * 6, y_coord);
	}
}

void CGraph::plot(int numberOfPoints, double *xVector, double *yVector, RGBColor color)
{
	if (!(xVector&&yVector))
	{
		throw std::exception("Null pointer exception\n");
	}
	else if (numberOfPoints>width-2*PADDING)
	{
		throw std::exception("Too many points for this graph\n");
	}
	else
	{
		int exY = (int)floor(((yVector[0] - yAxis.left) / yAxis.length() * (this->height)));
		int x = (int)floor(((xVector[0] - xAxis.left) / xAxis.length() * (this->width - 2 * PADDING)) + PADDING);
		for (int i = 0; i < numberOfPoints; ++i, x++)
		{
			int y = (int)floor(((yVector[i] - yAxis.left) / yAxis.length() * (this->height)));
			if (y - exY >= 2)
			{
				while (y - exY >= 2)
				{
					graph->putPixel(color, ++exY, x);
				}
			}
			else if (y - exY <= -2)
			{
				while (y - exY <= -2)
				{
					graph->putPixel(color, --exY, x);
				}
			}
			exY = y;
			graph->putPixel(color, y, x);
		}

	}
	
}


