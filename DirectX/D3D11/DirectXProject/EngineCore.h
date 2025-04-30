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

	// �����찡 ������ �Ŀ�, �ʱ�ȭ�ϰ� ���� ���� ó���մϴ�.
	void Start();
	// ���踦 ������Ʈ�Ѵ�.
	void Update();
	// �������� �����Ѵ�.
	void Render() {}
	// �������� ����Ǳ� ��, ���࿡ ����ߴ� �ڿ��� ��� �����Ѵ�.
	void Release();

	void Pause();
	void Unpause();

private:
	// ��� fps�� ����Ͽ� ������ â�� ���� ���������� �������Ѵ�.
	void CalculateFrameStats();

private:
	std::shared_ptr<EngineWindow> mWindow;
	std::shared_ptr<EngineGraphic> mGraphic;
	std::shared_ptr<EngineTimer> mTimer;

};


#endif // !__DEFINE_EngineCore_H_
