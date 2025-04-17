#include "Point.h"
#include <cmath>

double Point::Distance(Point* A, Point* B)
{
	if (nullptr == A || nullptr == B)
	{
		return 0.0f;
	}

	return std::sqrt(std::pow(A->x - B->x, 2) + std::pow((A->y - B->y), 2));
}