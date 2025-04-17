#pragma once


class Point
{
public:
	static double Distance(Point* A, Point* B);

public:
	int x, y;

public:
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int pos_x, int pos_y)
		: x(pos_x)
		, y(pos_y)
	{

	}

};