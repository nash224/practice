#pragma once

#ifndef __DEFINE_ENGINEWINDOW_H_
#define __DEFINE_ENGINEWINDOW_H_

#include <windows.h>
#include <memory>
#include <string>
#include <functional>

class EngineGraphic;

typedef struct WindowPos
{
	int X;
	int Y;
} WinPos;

typedef struct WinowSize
{
	int Width;
	int Height;
} WinSize;

class EngineWindow
{
public:
	static const WinSize& GetWindowSize() { return mWindowSize; };
	static const WinPos& GetWindowPos() { return mWindowPos; };

	static WinSize mWindowSize;
	static WinPos mWindowPos;

public:
	// constructor & destructor
	EngineWindow();
	virtual ~EngineWindow() {}

	// delete function
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	HINSTANCE AppInst() const
	{
		return mhAppInst;
	}
	HWND MainWnd() const 
	{
		return mhMainWnd;
	};


	// 화면의 비율을 반환한다.
	float AspectRatio() const { return static_cast<float>(mWindowSize.Width / mWindowSize.Height); }

	const std::wstring& GetWindowCaption() const { return mMainWndCaption; };
	void SetWindowCaption(std::wstring_view _Caption) { mMainWndCaption = _Caption; }
	void SetWindowTitle(std::wstring_view _Title);

	// 윈도우를 생성하고 초기화를 수행합니다.
	int WinStart(_In_ HINSTANCE hInstance);

	// 게임 루프, 게임 논리를 처리합니다.
	int Run(HINSTANCE _hInst,
		void(*_CoreStart)(), void(*_CoreUpdate)(), void(*_CoreEnd)());

	// 윈도우가 생성한 후에, 초기화하고 싶은 일을 처리합니다.
	virtual bool Init() { return true; }
	// 창의 크기가 변경되었을 경우 호출됩니다.
	// 목적: DirectX Backbuffer 초기화를 다시 수행합니다.
	virtual void OnResize();
	// 메세지 처리하는 방식을 사용자가 직접 구현한다.
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// 응용 프로그램이 종료하기 전에 하고싶은 일을 처리한다.
	virtual void Release();

	// 입력을 처리합니다.
	void OnMouseDown(WPARAM _btnState, int _x, int _y) {}
	void OnMouseUp(WPARAM _btnState, int _x, int _y) {}
	void OnMouseMove(WPARAM _btnState, int _x, int _y) {}

	void Pause();
	void Unpause();

	// 화면이 조정될 시 호출됩니다.
	std::function<void()> mCallBack_OnResize;
	// 화면이 정지될 시 호출됩니다.
	std::function<void()> mCallBack_OnPause;
	// 화면이 정지가 풀릴 시 호출됩니다.
	std::function<void()> mCallBack_OnUnpause;

private:
	ATOM MyRegisterClass(HINSTANCE hInstance) const;
	BOOL InitInstance();

private:
	HINSTANCE mhAppInst;  // 응용 프로그램 핸들
	HWND      mhMainWnd;  // 메인 윈도우 핸들
	bool      mAppPaused = false; // 응용 프로그램 정지 변수
	bool      mMinimized = false; // 화면 최소화 유무
	bool      mMaximized = false; // 화면 최대화 유무
	bool      mResizing  = true;  // 화면 크기 조정 유무

	std::wstring mMainWndCaption; // 윈도우 타이틀
	std::wstring mMainWndClass;   // 윈도우 클래스 이름

};

#endif // !__DEFINE_ENGINEWINDOW_H_