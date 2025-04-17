// EX_Producer&ConsumerPattern.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <cassert>

// 생산자-소비자 패턴
// 생산자가 리소스를 생산하면 소비자에서 생산했던 자원을 빼서 일을 처리하는 패턴
// 생산자와 소비자는 각각의 쓰레드에서 실행된다.

// 해당 예제는 경쟁조건이 발생하는 예기치 못하는 상황이 발생함
// 어떻게 고쳐야할지 모르겠음
// TODO: @me 경쟁조건 발생한 코드 수정

constexpr int NUMBER_OF_JOBS = 20;
constexpr int DELAY_MS = 200;

typedef unsigned long long data_type;

class HardJob
{
public:
	HardJob(std::vector<data_type>&& _Job, std::string_view _ResName) noexcept
		: mRes(_Job)
		, mName(_ResName)
	{
		std::cout << mName << "을 받았습니다.\n";
	}

	data_type operator()()
	{
		data_type Result = 0;
		const data_type SIZE = static_cast<data_type>(mRes.size());
		for (data_type i = 0; i < SIZE; i++)
		{
			Result += mRes[i];
		}

		std::string MSG = mName + "을 실행한 결과는 " + std::to_string(Result) + "입니다.\n";
		std::cout << MSG;

		return Result;
	}

private:
	std::vector<data_type> mRes;
	std::string mName;

};


void Producer(std::mutex& _m, std::queue<HardJob>& _MSG, int* _JobCount, std::condition_variable& _cv);
void Consumer(std::mutex& _m, std::queue<HardJob>& _MSG, int* _JobCount, std::condition_variable& _cv, std::vector<data_type>& _Results);

int main()
{
	const int NUM_OF_WORKER = 5;
	std::vector<std::thread> Producers;
	std::vector<std::thread> Consumers;
	std::mutex m;
	std::condition_variable cv;

	int ProduceCount = 0;
	std::queue<HardJob> Jobs;
	std::vector<data_type> Results;

	data_type Result = 0;

	for (int i = 0; i < NUM_OF_WORKER; i++)
	{
		Producers.push_back(std::thread(Producer, std::ref(m), std::ref(Jobs), &ProduceCount, std::ref(cv)));
	}

	for (int i = 0; i < NUM_OF_WORKER; i++)
	{
		Consumers.push_back(std::thread(Consumer, std::ref(m), std::ref(Jobs), &ProduceCount, std::ref(cv), std::ref(Results)));
	}

	for (std::thread& Producer : Producers)
	{
		Producer.join();
	}

	// 공급자가 할일을 모두 끝냈으니 모두에게 일어나라고 지시한다.
	cv.notify_all();

	for (std::thread& Consumer : Consumers)
	{
		Consumer.join();
	}
}

void Producer(std::mutex& _m, std::queue<HardJob>& _MSG, int* _Count, std::condition_variable& _cv)
{
	assert(nullptr != _Count);
	while (true)
	{
		const int NUM =(*_Count);

		if (NUMBER_OF_JOBS < NUM)
		{
			break;
		}
		
		// 쓰레드를 딜레이 시간만큼 재운다.
		// 쓰레드가 리소스를 생상한다.
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));

		const std::string ResName = std::string("작업번호") + std::to_string(NUM);

		const data_type RES_SIZE = static_cast<data_type>(50000 * (NUM + 1));
		std::vector<data_type> Res = std::vector<data_type>(RES_SIZE);
		for (data_type i = 0; i < RES_SIZE; i++)
		{
			Res[i] = i;
		}

		// 생산한 리소스를 메세지 큐에 넣는다.
		// 한 쓰레드만 접근가능 하도록 뮤텍스를 건다.
		_m.lock();
		_MSG.push(HardJob(std::move(Res), ResName));
		++(*_Count);
		_m.unlock();

		// cv로 인해 블로킹이된 쓰레드를 하나 깨운다.
		// 단일 consumer 쓰레드에게 메세지 알림을 보낸다.
		_cv.notify_one();
	}
}

void Consumer(std::mutex& _m, std::queue<HardJob>& _MSG, int* _JobCount, std::condition_variable& _cv, std::vector<data_type>& _Results)
{
	assert(nullptr != _JobCount);
	while (_Results.size() < NUMBER_OF_JOBS)
	{
		// lock_guard와 다르게 lock unlock을 할 수 있다.
		// lock_guard와 마찬가지로 생성자에서 lock을 수행한다.
		std::unique_lock<std::mutex> lk(_m);
		// wait 조건이 거짓이면 누군가 꺠워주지 않을때까지 블로킹
		_cv.wait(lk, [&]
			{
				return !_MSG.empty() || ((*_JobCount) == NUMBER_OF_JOBS);
			});

		// 메세지가 비어있다면 할일이 없는 쓰레드가 CPU 연산을 차지하지 않도록 쓰레드를 잠시 재운다.
		if (true == _MSG.empty())
		{
			lk.unlock();
			continue;
		}

		// 최적화는 무시
		HardJob Job = _MSG.front();
		_MSG.pop();
		lk.unlock();

		// 많이 걸리는 작업은 임계영역에서 제외한다.
		const data_type Sum = Job();

		lk.lock();
		_Results.push_back(Sum);
		lk.unlock();
	}
}
