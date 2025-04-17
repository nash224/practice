// MyString.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <crtdbg.h>
#include "CString.h"
#include "String.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (false)
	{
		const int Result = my_std::strlen("Hello");
		char* CopyStr = my_std::strcpy("Hello");
		char* AppendStr = my_std::strcat("Hello", " World!");

		const bool ValueA = my_std::strcmp(AppendStr, AppendStr);
		const bool ValueB = my_std::strcmp(AppendStr, "Hello World!");

		std::cout << AppendStr << "\n";

		delete CopyStr;
		delete AppendStr;
	}

	if (false)
	{
		std::string Str;
		const size_t capa = Str.capacity();
		const size_t len = Str.length();
		int a = 0;
	}

	if (true)
	{
		std::string Str = "Hello";
		std::string StrA = " fdsa";
		const char* Data = StrA.data();

		if (false)
		{
			char* Ptr = nullptr;
			StrA.copy(Ptr, 0);
			const size_t len = StrA.length();
			StrA.substr();
		}
	}

	if (true)
	{
		my_std::string Str;
		my_std::string StrB;
		StrB = " sdfsfds";
		Str.reserve(5);
		Str.resize(10);
		Str = "Rellow";
		Str = "Rellowsssssssasddddd";
		Str = "Rellowsssssssasddddddds";
		Str = "Hello";
		const char ResultAt = Str.at(2);
		Str[3] = 'R';
		const char ResultBack = Str.back();
		const char ResultFront = Str.front();
		Str.Append("abc");

		my_std::string StrC = Str + StrB;
		StrB += "f";
	}
}
