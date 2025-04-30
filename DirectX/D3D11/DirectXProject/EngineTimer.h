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

	inline float GetDeltaTime() const { return mDeltaTime; }
	inline double GetDoubleTime() const { return mDoubleTime; }

	// 실행했던 시간을 반환한다.
	float TotalTime() const;

	void Reset(); // 게임 루프 이전에 호출
	void Start(); // 시간을 다시 재생시킨다.
	void Stop();  // 시간을 멈춘다.
	void Tick();  // 매 프레임마다 업데이트를 수행한다.

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
