#pragma once

class Point;

class Geometry
{
public:
	Geometry()
	{
		num_points = 0;
	}

	~Geometry();

	void AddPoint(const Point& point);

	// ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
	void PrintDistance() const;

	// ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
	// ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
	// �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
	// ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
	void PrintNumMeets();

private:
	// �� 100 ���� �����ϴ� �迭.
	Point* point_array[100] = {nullptr,};
	int num_points;

};