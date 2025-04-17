// EX_Callback.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 예제만 포함됩니다.

#include <iostream>
#include <string>
#include <array>

typedef void (*Callback)(const char* _MSG);

constexpr int gNumberOfFunction = 3;



void Greet(const char* _Str)
{
	std::cout << "Greet: " << _Str << '\n';
}

void Callback2printGreet(Callback _Func, const char* _Str)
{
	_Func(_Str);
}

void Func1(const char* _Str)
{
	std::cout << "Callback Func1: " << _Str << '\n';
}

void Func2(const char* _Str)
{
	std::cout << "Callback Func2: " << _Str << '\n';
}

void Func3(const char* _Str)
{
	std::cout << "Callback Func3: " << _Str << '\n';
}

int main()
{
	if (false)
	{
		Callback2printGreet(Greet, "Hello, World!");
	}

	if (true)
	{
		std::array<std::pair<Callback, std::string>, 3> arrFunctions =
		{
			std::make_pair(Func1, "Hello"),
			std::make_pair(Func2, "World"),
			std::make_pair(Func3, "!")
		};

		for (const std::pair<Callback, std::string>& pair : arrFunctions)
		{
			pair.first(pair.second.c_str());
		}
	}

	return 0;
}
