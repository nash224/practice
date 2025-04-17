// 01_Exception.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stdexcept>


double Div(double _v1, double _v2);

int main()
{
	try
	{
		Div(5, 2);
		Div(2, 6);
		Div(3, 0.0);
		Div(8, 2);
	}
	// _e 객체의 _Data 멤버변수에 던져진 메세지가 존재한다.
	// throw문에서 점프 받는 곳이다.
	catch (const std::exception& _e)
	{
		std::cout << "exception caught: " << _e.what() << "\n ";
	}

	// throw 문을 받을 catch문이 존재하지 않을 경우 stl 이 그걸 받아 터트려버린다.
	// 예외 발생(0x00007FFB04AFFB4C, 01_Exception.exe): Microsoft C++ 예외: std::invalid_argument, 메모리 위치 0x000000E4775DF8D8.
	Div(3, 0);

    std::cout << "Hello World!\n";
}

/* 정밀 부동소수점 나누기를 수행한다. */
double Div(double _v1, double _v2)
{
	if (0.0 == _v2)
	{
		throw std::invalid_argument("_v2 cannot be 0.");
	}

	return _v1 / _v2;
}