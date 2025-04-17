// 24_atomic.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <cassert>

// c++에서 연자성이란, 특정 명령어를 수행할 때, 
// 하나의 코어에서 명령어를 순서대로 수행하는 것
// 
// cpu 컴파일러는 결과 값에 영향을 주지 않는다면
// 성능을 챙기기 위해 명령어 순서를 재배치해버린다.
// 만약 다른 스레드에서 공유 메모리를 참조하게 된다면, 
// 예상과 달리 다른 값을 참조할 수 있는 이유도 컴파일러에 의해 최적화되서 그렇다.
// 
// atomic은 뮤텍스를 걸지 않아도 원자적 연산을 보장해 준다.
// 원자적 변수의 명령어를 수행할 때, 메모리 읽기와 쓰기를 동시에 진행한다.
// 

constexpr int LOOP_COUNT = 10000;
// 전역 변수는 알아서 0으로 초기화된다.
std::atomic<int> g_Count;

void JustCount()
{
	for (int i = 0; i < LOOP_COUNT; i++)
	{
		++g_Count;
	}
}

void Producer(std::atomic<bool>& _Sign, int* _pData);
void Consumer(std::atomic<bool>& _Sign, int* _pData);

int main()
{
	enum
	{
		atomic_operator,
		memory_order
	};

	switch (memory_order)
	{
	case atomic_operator:
	{
		const int NUM_OF_WORKER = 16;
		std::vector<std::thread> Workers;

		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(JustCount));
		}

		for (auto& T : Workers)
		{
			T.join();
		}

		std::cout << std::boolalpha << reinterpret_cast<void*>(&g_Count)
			<< "변수는 뮤텍스로 잠궈지지 않았는가? " << g_Count.is_lock_free() << '\n';
		std::cout << "모든 연산이 끝났습니다.\n 연산한 결과는 " << g_Count << "입니다. \n";
		/* output:
		모든 연산이 끝났습니다.
		연산한 결과는 160000입니다.
		*/
		break;
	}
	case memory_order:
	{
		int Data = 0;
		std::vector<std::thread> Workers;
		std::atomic<bool> Sign;

		Workers.push_back(std::thread(Producer, std::ref(Sign), &Data));
		Workers.push_back(std::thread(Consumer, std::ref(Sign), &Data));

		for (auto& T : Workers)
		{
			T.join();
		}
		break;
	}
	default:
		break;
	}
	
}

void Producer(std::atomic<bool>& _Sign, int* _pData)
{
	assert(nullptr != _pData);
	(*_pData) = 10;

	_Sign.store(true, std::memory_order_relaxed);
	std::memory_order_release
}

void Consumer(std::atomic<bool>& _Sign, int* _pData)
{
	// 신호를 받지 않았다면 무한 대기
	while (false == _Sign.load(std::memory_order_relaxed))
	{
	}

	std::cout << "Data: " << (*_pData) << '\n';
}
