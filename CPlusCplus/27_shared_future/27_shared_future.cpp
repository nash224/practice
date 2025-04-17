// 27_shared_future.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <vector>
#include <cassert>

void Start(std::shared_future<void>* _Sign, int _Num)
{
	assert(nullptr != _Sign);
	// 데이터를 전달받을 때까지 무한 대기
	_Sign->get();

	std::printf("%d번 출발!\n", _Num);
}

int main()
{
	const int NUM_OF_WORKER = 4;
	std::vector<std::thread> Workers;

	// 아무것도 주지 않고 신호만 알려주겠다.
	std::promise<void> p;
	// std::shared_future는 내부에 생성된 객체를 이동이 아닌 복사방식으로 전달해준다.
	// void를 넣으면 신호만 여러번 받을 수 있다.
	std::shared_future<void> future = p.get_future();

	for (int i = 0; i < NUM_OF_WORKER; i++)
	{
		Workers.push_back(std::thread(Start, &future, i + 1));
	}

	std::cout << "준비..\n";
	// 신호를 준다.
	p.set_value();
	std::cout << "땅!\n";

	for (auto& i : Workers)
	{
		i.join();
	}
}