#pragma once

class Interval
{
public:
	double left, right;
	Interval(double pLeft, double pRight) : left(pLeft < pRight ? pLeft : pRight), right(pLeft > pRight ? pLeft : pRight) {};

	double length()
	{
		return right - left;
	}
};

//A point on the graph
struct Point
{
	int x, y;
};
