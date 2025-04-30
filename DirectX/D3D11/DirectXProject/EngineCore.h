//***************************************************************************************
// EngineCore.h by nash224 Visual Studio (C++) 2025 All Rights Reserved.
//***************************************************************************************

#pragma once

#ifndef __DEFINE_EngineCore_H_
#define __DEFINE_EngineCore_H_

#include <memory>
#include <windows.h>
#include <string>
#include "TSingleton.h"
#include "EngineWindow.h"

class EngineWindow;
class EngineGraphic;
class EngineTimer;

class EngineCore : public TSingleton<EngineCore>
{
public:
	static const WinSize& GetWindowSize()
	{
		return GetInstance()->mWindow->GetWindowSize();
	}
	static const WinPos& GetWindowPos()
	{
		return GetInstance()->mWindow->GetWindowPos();
	}

public:
	static void EngineStart(HINSTANCE _hInst);

	// constructor & destructor
	EngineCore() {}
	~EngineCore() {}

	// delete function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	const std::wstring& GetWindowCaption() const;

	// 윈도우가 생성한 후에, 초기화하고 싶은 일을 처리합니다.
	void Start();
	// 세계를 업데이트한다.
	void Update();
	// 렌더링을 수행한다.
	void Render() {}
	// 전역으로 종료되기 전, 실행에 사용했던 자원을 모두 정리한다.
	void Release();

	void Pause();
	void Unpause();

private:
	// 평균 fps를 계산하여 윈도우 창의 제목에 프레임율을 렌더링한다.
	void CalculateFrameStats();

private:
	std::shared_ptr<EngineWindow> mWindow;
	std::shared_ptr<EngineGraphic> mGraphic;
	std::shared_ptr<EngineTimer> mTimer;

};


#endif // !__DEFINE_EngineCore_H_
