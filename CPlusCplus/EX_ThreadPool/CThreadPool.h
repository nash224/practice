#pragma once
#include <vector>
#include <thread>
#include <list>
#include <queue>
#include <functional>
#include <mutex>
#include <cassert>

class CThreadPool;

// 쓰레드에게 맡겨질 작업
class CJob
{
public:
	enum class EJobType
	{
		Job,
	};

public:
	CJob(std::function<void()>&& _Job)
		: mFunc(_Job)
	{

	}

	void operator()()
	{
		mFunc();
	}

	std::function<void()> mFunc;

};

class CThreadPool
{
	friend class Worker;

public:
	// 전달할 정수만큼 쓰레드를 생성한다.
	CThreadPool(int _Num)
	{
		AddThread(_Num);
	}

	// 소멸자에서 모든 스레드가 소멸된다.
	~CThreadPool()
	{
		bStop = true;
		mCondition.notify_all();
		for (std::thread& i : mWorkers)
		{
			i.join();
		}
	}

public:
	// 쓰레드를 구동한다.
	// 쓰레드 풀 대신 따로 작업자의 멤버함수 느낌이다.
	// 전역으로 빼야하는게 맞지만 편의상 그냥 뒀다.
	void Run();

	// 작업을 큐에 등록한다.
	void RegistJob(CJob&& _Job);

	void AddThread(int _Num = 1);

private:
	std::queue<CJob> Jobs;
	std::vector<std::thread> mWorkers;

	std::mutex mLock;
	std::condition_variable mCondition;
	bool bStop = false;

};
