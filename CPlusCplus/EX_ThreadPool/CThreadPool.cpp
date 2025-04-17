#include "CThreadPool.h"

void CThreadPool::Run()
{
	// init
	bool bLoop = true;

	// run
	while (bLoop)
	{
		// condition_value를 위한 lock
		std::unique_lock<std::mutex> Lock(mLock);

		// 작업이 들어올때까지 cpu점유를 하지않도록 재운다.
		mCondition.wait(Lock, [this]() -> bool
			{
				return (true == bStop) || (false == Jobs.empty());
			});

		// 풀의 소멸자 시점 이후로 루프를 종료시킨다.
		if (true == bStop)
		{
			break;
		}

		CJob j = std::move(Jobs.front());
		Jobs.pop();

		Lock.unlock();

		j();
	}

	// des
}

// 작업을 넣고 작업자를 하나 깨운다.
void CThreadPool::RegistJob(CJob&& _Job)
{
	assert(false == bStop);

	mLock.lock();
	Jobs.push(_Job);
	mLock.unlock();

	mCondition.notify_one();
}

void CThreadPool::AddThread(int _Num/* = 1*/)
{
	for (int i = 0; i < _Num; i++)
	{
		mWorkers.push_back(std::thread(&CThreadPool::Run, this));
	}
}