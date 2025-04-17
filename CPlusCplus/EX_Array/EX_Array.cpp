// EX_Array.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <crtdbg.h>

#include "Array.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TArray<TArray<int>> Arr(5);
	for (int i = 0; i < Arr.size(); i++)
	{
		Arr[i].Resize(5);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Arr[i][j] = (i + 1) * (j + 1);
			std::cout << Arr[i][j] << ' ';
		}

		std::cout << '\n';
	}

    std::cout << "Hello World!\n";
}
