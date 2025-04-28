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

	// 멈췄다면, 멈췄던 시간만큼 업데이트한다.
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
	// 정지된 상태면 업데이트하지 않는다.
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
	// 정지 시, 시간을 업데이트 하지 않는다.
	if (true == mStopped)
	{
		mDeltaTime = 0.0f;
		return;
	}

	// 프레임을 업데이트 한다.
	time_type CurTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);
	mCurTime = CurTime;

	mDoubleTime = static_cast<double>((mCurTime - mPrevTime) * mSecondsPerCount);
	mDeltaTime = static_cast<float>(mDoubleTime);

	mPrevTime = mCurTime;

	// 진행 시간이 음수가 되는걸 방지한다.
	mDeltaTime = (mDeltaTime < 0) ? 0.0f : mDeltaTime;
}

float EngineTimer::TotalTime() const
{
	// 일시 정지했던 시간은 제외하고 흐른시간을 반환한다.
	// 
	//                  |<-일시정지 시간 ->|
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
