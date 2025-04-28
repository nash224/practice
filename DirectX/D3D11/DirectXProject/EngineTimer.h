#pragma once

#ifndef __DEFINE_ENGINETIMER_H_
#define __DEFINE_ENGINETIMER_H_

class EngineTimer
{
public:
	using time_type = __int64;

	// constructor & destructor
	EngineTimer();
	~EngineTimer() {}

	// delete function
	EngineTimer(const EngineTimer& _Other) = delete;
	EngineTimer(EngineTimer&& _Other) noexcept = delete;
	EngineTimer& operator=(const EngineTimer& _Other) = delete;
	EngineTimer& operator=(EngineTimer&& _Other) = delete;

	// 흐른 시간을 반환합니다.
	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	// 흐른 시간을 반환합니다.
	double GetDoubleTime() const
	{
		return mDoubleTime;
	}

	// 멈췄던 시간을 제외한, 진행했던 시간
	float TotalTime() const;

	// 시간 리셋
	void Reset();
	// 시간 측정 시작
	void Start();
	// 시간 정지
	void Stop();
	// 시간 업데이트
	void Tick();

private:
	time_type mBaseTime   = 0; // 리셋 이후로부터, 진행한 시간
	time_type mPausedTime = 0; // 정지한 시간
	time_type mStopTime   = 0; // 정지했을 때 시간
	time_type mPrevTime   = 0; // 이전 프레임 시간
	time_type mCurTime    = 0; // 현재 프레임 시간

	time_type mSecondsPerCount = 0;

	double mDoubleTime = 0.0;
	float mDeltaTime = 0.0f;

	bool mStopped = false;

};


#endif // !__DEFINE_ENGINETIMER_H_
