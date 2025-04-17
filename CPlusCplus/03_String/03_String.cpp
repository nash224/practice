// 03_String.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS

#include <crtdbg.h>

#include <iostream>
#include <cstring>

// 절차지향적으로 c스타일의 문자열을 이해하고 구현해본다.
// c스타일의 배열 끝부분은 '\0' 문자가 들어있어야 한다.
// 따라서 문자열의 길이 + 1 만큼 할당해주어야한다.

char* CopyString(const char* _rscStr);
char* AppendString(const char* _Str1, const char* _Str2);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (false)
	{
		const char* Str1 = CopyString("Hello");
		std::cout << Str1 << "\n";
		delete Str1;
	}
	
	if (false)
	{
		const char* Str = AppendString("Hello", ", World!");
		std::cout << Str << "\n";
		delete Str;
	}

	if (false)
	{
		// 컴파일러가 자동으로 배열의 크기를 할당해준다.
		char Arr[] = "Hello";
		std::cout << "Str Size: " << sizeof(Arr) << "\n";
	}

	if (true)
	{
		const char* StrA = "154";
		char StrB[] = "154";
		if (StrA != StrB)
		{
			std::cout << "StrA와 StrB는 같지 않습니다.\n";
			std::cout << "StrA Address: " << reinterpret_cast<__int64>(StrA) << "\n";
			std::cout << "StrB Address: " << reinterpret_cast<__int64>(StrB) << "\n";
		}

		enum { Same = 0 };
		if (Same == strcmp(StrA, StrB))
		{
			std::cout << "strcmp로 비교한 StrA, StrB의 값은 사전적으로 같습니다.\n";
		}
	}

	if (false)
	{
		std::string Str = "Hello";
		const char* CStr = Str.c_str();
		Str = "Change Value";
		CStr;
		int a = 0;
	}
	
	if (false)
	{
		// 제공되지 않는 문자열 
		// auto Str = "Hello"s;
	}

	if (true)
	{
		// 로우 문자열 리터럴은 이스케이프 시퀀스를 사용하지 않고도 문자열로 표현된다.
		std::string Str = R"(Hello, 
World!)"; // 컴파일 가능 


		std::cout << Str;
	}
}

/* 문자열을 복사하여 반환한다. 메모리 정리는 따로 하지않는다. */
char* CopyString(const char* _srcStr)
{
	char* Result = new char[strlen(_srcStr) + 1];
	strcpy(Result, _srcStr);
	return Result;
}
/* 두 문자열을 붙여 반환한다. */
char* AppendString(const char* _Str1, const char* _Str2)
{
	char* Result = new char[strlen(_Str1) + strlen(_Str2) + 1];
	strcpy(Result, _Str1);
	strcat(Result, _Str2);
	return Result;
}