#include "EngineTimer.h"

#include <windows.h>


EngineTimer::EngineTimer()
{
	time_type countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

void EngineTimer::Reset()
{
	time_type CurTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);

	mBaseTime = CurTime;
	mCurTime  = CurTime;
	mStopTime = 0;
	mStopped  = false;	
}

void EngineTimer::Start()
{
	time_type StartTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&StartTime);

	// ����ٸ�, ����� �ð���ŭ ������Ʈ�Ѵ�.
	if (true == mStopped)
	{
		mPausedTime += (StartTime - mStopTime);

		mPrevTime = StartTime;
		mStopTime = 0;
	}

	mStopped = false;
}

void EngineTimer::Stop()
{
	// ������ ���¸� ������Ʈ���� �ʴ´�.
	if (true == mStopped)
	{
		return;
	}

	time_type CurTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);

	mStopTime = CurTime;
	mStopped = true;
}

void EngineTimer::Tick()
{
	// ���� ��, �ð��� ������Ʈ ���� �ʴ´�.
	if (true == mStopped)
	{
		mDeltaTime = 0.0f;
		return;
	}

	// �������� ������Ʈ �Ѵ�.
	time_type CurTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);
	mCurTime = CurTime;

	mDoubleTime = static_cast<double>((mCurTime - mPrevTime) * mSecondsPerCount);
	mDeltaTime = static_cast<float>(mDoubleTime);

	mPrevTime = mCurTime;

	// ���� �ð��� ������ �Ǵ°� �����Ѵ�.
	mDeltaTime = (mDeltaTime < 0) ? 0.0f : mDeltaTime;
}

float EngineTimer::TotalTime() const
{
	// �Ͻ� �����ߴ� �ð��� �����ϰ� �帥�ð��� ��ȯ�Ѵ�.
	// 
	//                  |<-�Ͻ����� �ð� ->|
	// -----*-----------*-----------------*-------------*--------------> t
	// mBaseTime	mStopTime		  mStartTime	 mCurTime

	time_type TotalTime = 0;
	if (true == mStopped)
	{
		TotalTime = (mStopTime - mPausedTime - mBaseTime) * mSecondsPerCount;
	}
	else
	{
		TotalTime = (mCurTime - mPausedTime - mBaseTime) * mSecondsPerCount;
	}

	return static_cast<float>(TotalTime);
}
