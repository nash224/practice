#pragma once
#include <vector>
#include <thread>
#include <list>
#include <queue>
#include <functional>
#include <mutex>
#include <cassert>

class CThreadPool;

// �����忡�� �ð��� �۾�
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
	// ������ ������ŭ �����带 �����Ѵ�.
	CThreadPool(int _Num)
	{
		AddThread(_Num);
	}

	// �Ҹ��ڿ��� ��� �����尡 �Ҹ�ȴ�.
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
	// �����带 �����Ѵ�.
	// ������ Ǯ ��� ���� �۾����� ����Լ� �����̴�.
	// �������� �����ϴ°� ������ ���ǻ� �׳� �״�.
	void Run();

	// �۾��� ť�� ����Ѵ�.
	void RegistJob(CJob&& _Job);

	void AddThread(int _Num = 1);

private:
	std::queue<CJob> Jobs;
	std::vector<std::thread> mWorkers;

	std::mutex mLock;
	std::condition_variable mCondition;
	bool bStop = false;

};
