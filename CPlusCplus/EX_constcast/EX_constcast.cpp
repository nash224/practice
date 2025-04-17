// EX_constcast.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

const int* gNumber;

int main()
{
	if (false)
	{
		// Data영역 const_cast
		int* Ptr = const_cast<int*>(gNumber);
		(*Ptr) = 5;								// 쓰기 영역 접근 위한
		std::cout << (*gNumber) << '\n';
	}

	if (true)
	{
		// Stack영역 const_cast
		const int Value = 5;
		int* Ptr = const_cast<int*>(&Value);
		*Ptr = 10;								// 재정의 가능
		std::cout << *Ptr << '\n';				// 10출력
		std::cout << Value << '\n';				// 5출력
	}
	
	if (true)
	{
		// Heap영역 const_cast
		const int* NewPtr = new int;
		int* Ptr = const_cast<int*>(NewPtr);
		*Ptr = 15;								// 재정의 가능
		std::cout << (*NewPtr) << '\n';			// 15출력
	}
}
