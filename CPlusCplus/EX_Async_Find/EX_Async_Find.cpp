// EX_Async_Find.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <future>
#include <thread>
#include <cassert>
#include <chrono>

class Timer
{
public:
	using duration_type = std::chrono::nanoseconds;

public:
	void Start()
	{
		SPoint = std::chrono::high_resolution_clock::now();
	}
	long long Stop() const
	{
		std::chrono::steady_clock::time_point EPoint = std::chrono::high_resolution_clock::now();
		duration_type Check = std::chrono::duration_cast<duration_type>(EPoint - SPoint);
		return static_cast<long long>(Check.count());
	}

private:
	std::chrono::steady_clock::time_point SPoint;

};

constexpr int RES_SIZE = 100'000'000;

void async_find(
	std::promise<std::vector<int>::const_iterator>* _p, 
	std::vector<int>::const_iterator _Start, 
	std::vector<int>::const_iterator _End, 
	const int& _Data)
{
	assert(nullptr != _p);
	for (; _Start != _End; ++_Start)
	{
		if (_Data == *_Start)
		{
			_p->set_value(_Start);
			return;
		}
	}
}


std::vector<int>::const_iterator find(const std::vector<int>& _Res, const int& _Data)
{
	const int RES_SIZE = static_cast<int>(_Res.size());

	const int NUM_OF_WORKER = 16;
	std::vector<std::thread> Workers;

	std::promise<std::vector<int>::const_iterator> p;
	std::future<std::vector<int>::const_iterator> future = p.get_future();

	const int SEARCH_COUNT_PER_THREAD = RES_SIZE / NUM_OF_WORKER;
	for (int i = 0; i < NUM_OF_WORKER; i++)
	{
		Workers.push_back(std::thread(
			async_find, 
			&p,
			_Res.begin() + (i * SEARCH_COUNT_PER_THREAD), 
			_Res.begin() + ((i + 1) * SEARCH_COUNT_PER_THREAD), 
			std::cref(_Data)));
	}

	for (std::thread& i : Workers)
	{
		i.join();
	}

	return future.get();
}

int main()
{
	Timer T;

	std::vector<int> Res = std::vector<int>(RES_SIZE);
	for (int i = 0; i < RES_SIZE; i++)
	{
		Res[i] = i;
	}

	const int SearchData = 16'000'000;

	T.Start();
	std::vector<int>::const_iterator FindIter = find(Res, SearchData);
	long long SearchTime = T.Stop();

	if (FindIter == Res.end())
	{
		std::cout << "데이터를 찾지 못했습니다.\n";
		return 0;
	}
	std::cout << "find함수 실행 시간" << SearchTime << '\n';

	T.Start();
	FindIter = std::find(Res.begin(), Res.end(), SearchData);
	SearchTime = T.Stop();
	std::cout << "std::find함수 실행 시간" << SearchTime << '\n';
	// Resource Size = 10000
	// Find Res = 6000
	/* otuput:
	find함수 실행 시간12295300
	std::find함수 실행 시간18200
	*/

	// 내가 만든 find 알고리즘 비용이 더 많이 발생했다.
	// 아마 쓰레드를 만들고 소멸하는 비용 때문일지 모른다.
	// 자료 크기를 늘려보고 찾는 숫자도 멀리 해봤는데, 여전히 내 find가 비용이 더 많다.
}