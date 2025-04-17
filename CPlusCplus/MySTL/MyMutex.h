#pragma once
#include <atomic>


class MyMutex
{
public:
	MyMutex()
	{
		mValue.store(false);
	}
	~MyMutex() {}

	void lock();
	void unlock();

protected:

private:
	std::atomic<bool> mValue;
	bool IsLock = false;

};