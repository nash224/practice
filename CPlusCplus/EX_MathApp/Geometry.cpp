#include "Geometry.h"
#include <assert.h>
#include <vector>
#include <iostream>

#include "Point.h"

Geometry::~Geometry()
{
	for (int i = 0; i < num_points; i++)
	{
		if (nullptr != point_array[i])
		{
			delete point_array[i];
			point_array[i] = nullptr;
		}
	}
}

void Geometry::AddPoint(const Point& point)
{
	point_array[num_points] = new Point(point.x, point.y);
	++num_points;
}

void Geometry::PrintDistance() const
{
	static std::vector<double> Distances;
	Distances.clear();

	// 미리 할당
	const int Buffer_size = (num_points - 1)* (num_points - 1);
	Distances.reserve(Buffer_size);

	for (int i = 0; i < num_points; i++)
	{
		for (int j = 0; j < num_points; j++)
		{
			if (i == j)
			{
				continue;
			}

			Point* PointA = point_array[i];
			Point* PointB = point_array[j];
			
			assert(nullptr != PointA && nullptr != PointB);

			const double Dist = Point::Distance(PointA, PointB);
			Distances.push_back(Dist);
		}
	}

	const int SIZE = static_cast<int>(Distances.size());
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << Distances[i] << ' ';
	}

	std::cout << '\n';
}

void Geometry::PrintNumMeets()
{

}
