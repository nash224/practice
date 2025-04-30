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


	// ȭ���� ������ ��ȯ�Ѵ�.
	float AspectRatio() const { return static_cast<float>(mWindowSize.Width / mWindowSize.Height); }

	const std::wstring& GetWindowCaption() const { return mMainWndCaption; };
	void SetWindowCaption(std::wstring_view _Caption) { mMainWndCaption = _Caption; }
	void SetWindowTitle(std::wstring_view _Title);

	// �����츦 �����ϰ� �ʱ�ȭ�� �����մϴ�.
	int WinStart(_In_ HINSTANCE hInstance);

	// ���� ����, ���� ���� ó���մϴ�.
	int Run(HINSTANCE _hInst,
		void(*_CoreStart)(), void(*_CoreUpdate)(), void(*_CoreEnd)());

	// �����찡 ������ �Ŀ�, �ʱ�ȭ�ϰ� ���� ���� ó���մϴ�.
	virtual bool Init() { return true; }
	// â�� ũ�Ⱑ ����Ǿ��� ��� ȣ��˴ϴ�.
	// ����: DirectX Backbuffer �ʱ�ȭ�� �ٽ� �����մϴ�.
	virtual void OnResize();
	// �޼��� ó���ϴ� ����� ����ڰ� ���� �����Ѵ�.
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// ���� ���α׷��� �����ϱ� ���� �ϰ���� ���� ó���Ѵ�.
	virtual void Release();

	// �Է��� ó���մϴ�.
	void OnMouseDown(WPARAM _btnState, int _x, int _y) {}
	void OnMouseUp(WPARAM _btnState, int _x, int _y) {}
	void OnMouseMove(WPARAM _btnState, int _x, int _y) {}

	void Pause();
	void Unpause();

	// ȭ���� ������ �� ȣ��˴ϴ�.
	std::function<void()> mCallBack_OnResize;
	// ȭ���� ������ �� ȣ��˴ϴ�.
	std::function<void()> mCallBack_OnPause;
	// ȭ���� ������ Ǯ�� �� ȣ��˴ϴ�.
	std::function<void()> mCallBack_OnUnpause;

private:
	ATOM MyRegisterClass(HINSTANCE hInstance) const;
	BOOL InitInstance();

private:
	HINSTANCE mhAppInst;  // ���� ���α׷� �ڵ�
	HWND      mhMainWnd;  // ���� ������ �ڵ�
	bool      mAppPaused = false; // ���� ���α׷� ���� ����
	bool      mMinimized = false; // ȭ�� �ּ�ȭ ����
	bool      mMaximized = false; // ȭ�� �ִ�ȭ ����
	bool      mResizing  = true;  // ȭ�� ũ�� ���� ����

	std::wstring mMainWndCaption; // ������ Ÿ��Ʋ
	std::wstring mMainWndClass;   // ������ Ŭ���� �̸�

};

#endif // !__DEFINE_ENGINEWINDOW_H_