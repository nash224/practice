#include "EngineWindow.h"

#include <windowsx.h>

#include "framework.h"
#include "Resource.h"
#include "Header.h"
#include "Constant.h"

#include "EngineGraphic.h"

#define MAX_LOADSTRING 100

namespace
{
    // wcex.lpfnWndProc에 객체 함수 포인터를 할당해주지 못하기 때문에 
    // WndProc 내부에서 EngineWindow 멤버함수를 대신 호출해줘야 한다.
    EngineWindow* gWindow = nullptr;
}


//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

WinSize EngineWindow::mWindowSize = { engine::window::WinSize::Width, engine::window::WindowSize::Height };
WinPos EngineWindow::mWindowPos = { engine::window::WinPos::XPos, engine::window::WinPos::YPos };

void EngineWindow::SetWindowTitle(std::wstring_view _Title)
{
	SetWindowText(mhMainWnd, mMainWndCaption.c_str());

}

EngineWindow::EngineWindow()
	: mhAppInst(0)
	, mhMainWnd(0)
	, mMainWndCaption(L"DirectXApplication")
	, mMainWndClass(L"DirectXClass")
{
    // 전역 윈도우 메세지 함수를 호출 목적으로
    // 윈도우 객체 포인터를 전역변수에 할당한다.
    gWindow = this;
}

void EngineWindow::OnResize()
{
    if (mCallBack_OnResize)
    {
		mCallBack_OnResize();
    }
}

// 윈도우를 생성하고 초기화를 수행합니다.
int EngineWindow::WinStart(HINSTANCE _hInst)
{
    mhAppInst = _hInst;

    // 전역 문자열을 초기화합니다.
    MyRegisterClass(_hInst);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance())
    {
        return FALSE;
    }

    return TRUE;
}


//
//   함수: InitInstance(HINSTANCE)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL EngineWindow::InitInstance()
{
    RECT R = { 
        EngineWindow::mWindowPos.X,
        EngineWindow::mWindowPos.Y,
        EngineWindow::mWindowSize.Width,
        EngineWindow::mWindowSize.Height,
    };

    // 클라이언트 창 크기를 조절합니다.
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    const int nWidth  = R.right - R.left;
    const int nHeight = R.bottom - R.top;

    mhMainWnd = CreateWindow(
        mMainWndClass.c_str(),
        mMainWndCaption.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        nWidth, nHeight,
        0, 0, 
        mhAppInst, 0);

    if (!mhMainWnd)
    {
        MessageBoxAssert(L"Failed to create window.");
        return FALSE;
    }

    ShowWindow(mhMainWnd, SW_SHOW);
    UpdateWindow(mhMainWnd);

    return TRUE;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM EngineWindow::MyRegisterClass(HINSTANCE hInstance) const
{
    WNDCLASS wcex;

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTXPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = mMainWndClass.data();

    return RegisterClass(&wcex);
}

LRESULT EngineWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // 왼도우가 활성화되거나 비활성화될 경우 
        // WM_ACTIVATE가 활성화됩니다.
    case WM_ACTIVATE:
    {
        if (LOWORD(wParam) == WA_INACTIVE)
        {
			Pause();
        }
        else
        {
			Unpause();
        }
    }
    // 창을 조절할 경우 활성화
    break;
    case WM_SIZE:
    {
        EngineWindow::mWindowSize.Width  = LOWORD(lParam);
        EngineWindow::mWindowSize.Height = HIWORD(lParam);
        if (wParam == SIZE_MINIMIZED)
        {
            mAppPaused = true;
            mMinimized = true;
            mMaximized = false;
        }
        else if (wParam == SIZE_MAXIMIZED)
        {
            mAppPaused = false;
            mMinimized = false;
            mMaximized = true;
            OnResize();
        }
        else if (wParam == SIZE_RESTORED)
        {
            // 축소 -> 복원
            if (mMinimized)
            {
                mAppPaused = false;
                mMinimized = false;
                OnResize();
            }
            // 전체 창 비활성화
            else if (mMaximized)
            {
                mAppPaused = false;
                mMaximized = false;
                OnResize();
            }
            else if (mResizing)
            {
                // 크기를 키우는 중이라면 아무것도 하지 않는다.
            }
            else
            {
                OnResize();
            }
        }
    }
    break;
    case WM_ENTERSIZEMOVE:
    {
        mResizing = true;
		Pause();
    }
    break;
    case WM_EXITSIZEMOVE:
    {
        mResizing = false;
		Unpause();
        OnResize();
    }
    break;
    //case WM_COMMAND:
    //{
    //    int wmId = LOWORD(wParam);
    //    // 메뉴 선택을 구문 분석합니다:
    //    switch (wmId)
    //    {
    //    case IDM_ABOUT:
    //        DialogBox(mhAppInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //        break;
    //    case IDM_EXIT:
    //        DestroyWindow(hWnd);
    //        break;
    //    default:
    //        return DefWindowProc(hWnd, message, wParam, lParam);
    //    }
    //}
    //break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MENUCHAR:
    {
        // alt-tab 시, '삐-' 소리를 내지 않도록 설정
        return MAKELRESULT(0, MNC_CLOSE);
    }
    // 화면이 너무 작게 조절되지 않도록 설정
    case WM_GETMINMAXINFO:
    {
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    {
        OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    }
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    }
    case WM_MOUSEMOVE:
    {
        OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void EngineWindow::Release()
{

}

void EngineWindow::Pause()
{
	if (mCallBack_OnUnpause)
	{
		mCallBack_OnPause();
	}
	mAppPaused = true;
}

void EngineWindow::Unpause()
{
	if (mCallBack_OnUnpause)
	{
		mCallBack_OnUnpause();
	}
	mAppPaused = false;
}

int EngineWindow::Run(HINSTANCE _hInst,
	void(*_CoreStart)(), void(*_CoreUpdate)(), void(*_CoreEnd)())
{
	WinStart(_hInst);
	Init();

	_CoreStart();

    HACCEL hAccelTable = LoadAccelerators(mhAppInst, MAKEINTRESOURCE(IDC_DIRECTXPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			if (false == mAppPaused)
			{
				_CoreUpdate();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	_CoreEnd();

    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}