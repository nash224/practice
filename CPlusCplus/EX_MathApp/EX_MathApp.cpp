// EX_MathApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Point.h"
#include "Geometry.h"

int main()
{
	Geometry NewGeometry;

	NewGeometry.AddPoint({2,5});
	NewGeometry.AddPoint({6,2});
	NewGeometry.AddPoint({2,8});
	NewGeometry.AddPoint({9,5});
	NewGeometry.AddPoint({2,3});
	NewGeometry.PrintDistance();

    std::cout << "Hello World!\n";
}
