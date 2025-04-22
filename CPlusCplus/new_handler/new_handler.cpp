// new_handler.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

constexpr int MEM_ARR_SIZE = 10;
std::vector<std::unique_ptr<int*>> g_MemPtrArray;

void OutOfMem()
{
	std::cerr << "Unable to satisfy request for memory\n";
	g_MemPtrArray.clear();
	std::abort();
}

int main()
{
	// new 처리자 등록하고
	std::set_new_handler(OutOfMem);

	// 할당할 메모리 크기를 overflow 시킨다.
	// 내부에서 nullptr을 반환되고, 미리 지정해두었던 new 처리자가 실행된다.

	const int SIZE = MEM_ARR_SIZE;
	for (int i = 0; i < SIZE; i++)
	{
		g_MemPtrArray.emplace_back(
			std::make_unique<int*>(new int[1'000'000'000LL]));
	}
}