// EX_MyString.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "MyString.h"

int main()
{
	if (false)
	{
		MyString String = MyString("Hello World!");
		String.add_string("\n This is New World.");
		String.Insert(1, "TTT");
		String.Erase(1, 3);
		String.Find(0, "World");
		String.Insert(5, "c");
		std::cout << String;
	}

	if (false)
	{
		MyString StringA = "Hello";
		MyString StringB = "Hello";
		std::cout << "StringA == StringB: " << (StringA == StringB) << '\n';

		StringB.add_string("World!");
		std::cout << "StringA < StringB: " << (StringA < StringB) << '\n';
	}

	if (true)
	{
		MyString StrA = "Hello" + MyString(", World");
		MyString StrB = MyString("Hello") + ", World";
		std::cout << StrB[4] << '\n';
	}

	if (false)
	{
		std::string Str;
	}
}