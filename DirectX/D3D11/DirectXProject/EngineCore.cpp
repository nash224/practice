//***************************************************************************************
// EngineCore.cpp by nash224 Visual Studio (C++) 2025 All Rights Reserved.
//***************************************************************************************

#include "EngineCore.h"

#include <functional>
#include <string>
#include <sstream>

#include "Header.h"
#include "EngineWindow.h"
#include "EngineGraphic.h"
#include "EngineTimer.h"

void Start() 
{
	EngineCore::GetInstance()->Start();
}

void Update()
{
	EngineCore::GetInstance()->Update();
}

void End()
{
	EngineCore::GetInstance()->Release();
}


void EngineCore::EngineStart(HINSTANCE _hInst)
{
    engine::debug::LeakCheck();

    // Window 객체 생성
    EngineCore* pInstance = EngineCore::GetInstance();
    if (nullptr == pInstance)
    {
        MessageBoxAssert(L"failed to create an engine object.");
		return;
    }

	std::shared_ptr<EngineWindow> pWindow = std::make_shared<EngineWindow>();
	pInstance->mWindow = pWindow;
	pWindow->Run(_hInst, ::Start, ::Update, ::End);
}

const std::wstring& EngineCore::GetWindowCaption() const 
{ 
	return mWindow->GetWindowCaption(); 
}

void EngineCore::Start()
{
    // 반드시 윈도우가 초기화된 이후, EngineGraphic를 초기화해야 합니다.
	mTimer = std::make_shared<EngineTimer>();
    mGraphic = std::make_shared<EngineGraphic>();
	if (FALSE == mGraphic->Init(mWindow->MainWnd()))
	{
		MessageBoxAssertReturn(L"failed to create window.");
	}

	mWindow->mCallBack_OnResize = std::bind(&EngineGraphic::OnResize, mGraphic.get());
	mWindow->mCallBack_OnPause = std::bind(&EngineCore::Pause, this);
	mWindow->mCallBack_OnUnpause = std::bind(&EngineCore::Unpause, this);

	mTimer->Reset();
}

void EngineCore::Update()
{
	mTimer->Tick(); 
}

void EngineCore::Release()
{

}

void EngineCore::Pause()
{
	mTimer->Stop();
}

void EngineCore::Unpause()
{
	mTimer->Start();
}

void EngineCore::CalculateFrameStats()
{
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;

	++FrameCount;

	if (1.0f <= (mTimer->TotalTime() - TimeElapsed))
	{
		const float Fps = static_cast<float>(FrameCount);
		const float msPerFrame = 1000.0f / Fps;

		std::wostringstream wOut;
		wOut.precision(6);
		wOut << GetWindowCaption() << L"   "
			<< L"FPS: " << Fps << L"    "
			<< L"Frame Time: " << msPerFrame << L" (ms)";

		mWindow->SetWindowTitle(wOut.str());

		FrameCount = 0;
		TimeElapsed += 1.0f;
	}
}