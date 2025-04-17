#include "CThreadPool.h"

void CThreadPool::Run()
{
	// init
	bool bLoop = true;

	// run
	while (bLoop)
	{
		// condition_value�� ���� lock
		std::unique_lock<std::mutex> Lock(mLock);

		// �۾��� ���ö����� cpu������ �����ʵ��� ����.
		mCondition.wait(Lock, [this]() -> bool
			{
				return (true == bStop) || (false == Jobs.empty());
			});

		// Ǯ�� �Ҹ��� ���� ���ķ� ������ �����Ų��.
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

// �۾��� �ְ� �۾��ڸ� �ϳ� �����.
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