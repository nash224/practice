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

	// �帥 �ð��� ��ȯ�մϴ�.
	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	// �帥 �ð��� ��ȯ�մϴ�.
	double GetDoubleTime() const
	{
		return mDoubleTime;
	}

	// ����� �ð��� ������, �����ߴ� �ð�
	float TotalTime() const;

	// �ð� ����
	void Reset();
	// �ð� ���� ����
	void Start();
	// �ð� ����
	void Stop();
	// �ð� ������Ʈ
	void Tick();

private:
	time_type mBaseTime   = 0; // ���� ���ķκ���, ������ �ð�
	time_type mPausedTime = 0; // ������ �ð�
	time_type mStopTime   = 0; // �������� �� �ð�
	time_type mPrevTime   = 0; // ���� ������ �ð�
	time_type mCurTime    = 0; // ���� ������ �ð�

	time_type mSecondsPerCount = 0;

	double mDoubleTime = 0.0;
	float mDeltaTime = 0.0f;

	bool mStopped = false;

};


#endif // !__DEFINE_ENGINETIMER_H_
