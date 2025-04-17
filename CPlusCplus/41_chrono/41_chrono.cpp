// 41_chrono.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <chrono>

// chrono 라이브러리로 특정 간격 또는 시간을 표현할 수 있다.

// 높은 비용이 발생하는 함수
void HighCostFunc()
{
	const int SIZE = 100000000;
	int* Ptr = new int[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		Ptr[i] = i;
	}

	delete[] Ptr;
	Ptr = nullptr;
}

int main()
{
	// time_point는 현재까지 틱이 얼마만큼 발생했는지 알려준다.
	std::chrono::time_point<std::chrono::high_resolution_clock> Start 
		= std::chrono::high_resolution_clock::now();

	// 시간이 많이 걸리는 작업 수행
	HighCostFunc();

	std::chrono::time_point<std::chrono::high_resolution_clock> Stop
		= std::chrono::high_resolution_clock::now();
	
	// 시작점과 끝점의 간격을 duration 객체로 캐스팅
	std::chrono::nanoseconds Diff
		= std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start);

    std::cout << Diff.count() << "틱 발생.\n";
}