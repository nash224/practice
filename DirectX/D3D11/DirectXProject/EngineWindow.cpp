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
    // wcex.lpfnWndProc�� ��ü �Լ� �����͸� �Ҵ������� ���ϱ� ������ 
    // WndProc ���ο��� EngineWindow ����Լ��� ��� ȣ������� �Ѵ�.
    EngineWindow* gWindow = nullptr;
}


//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
    // ���� ������ �޼��� �Լ��� ȣ�� ��������
    // ������ ��ü �����͸� ���������� �Ҵ��Ѵ�.
    gWindow = this;
}

void EngineWindow::OnResize()
{
    if (mCallBack_OnResize)
    {
		mCallBack_OnResize();
    }
}

// �����츦 �����ϰ� �ʱ�ȭ�� �����մϴ�.
int EngineWindow::WinStart(HINSTANCE _hInst)
{
    mhAppInst = _hInst;

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    MyRegisterClass(_hInst);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance())
    {
        return FALSE;
    }

    return TRUE;
}


//
//   �Լ�: InitInstance(HINSTANCE)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL EngineWindow::InitInstance()
{
    RECT R = { 
        EngineWindow::mWindowPos.X,
        EngineWindow::mWindowPos.Y,
        EngineWindow::mWindowSize.Width,
        EngineWindow::mWindowSize.Height,
    };

    // Ŭ���̾�Ʈ â ũ�⸦ �����մϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
        // �޵��찡 Ȱ��ȭ�ǰų� ��Ȱ��ȭ�� ��� 
        // WM_ACTIVATE�� Ȱ��ȭ�˴ϴ�.
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
    // â�� ������ ��� Ȱ��ȭ
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
            // ��� -> ����
            if (mMinimized)
            {
                mAppPaused = false;
                mMinimized = false;
                OnResize();
            }
            // ��ü â ��Ȱ��ȭ
            else if (mMaximized)
            {
                mAppPaused = false;
                mMaximized = false;
                OnResize();
            }
            else if (mResizing)
            {
                // ũ�⸦ Ű��� ���̶�� �ƹ��͵� ���� �ʴ´�.
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
    //    // �޴� ������ ���� �м��մϴ�:
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
        // alt-tab ��, '��-' �Ҹ��� ���� �ʵ��� ����
        return MAKELRESULT(0, MNC_CLOSE);
    }
    // ȭ���� �ʹ� �۰� �������� �ʵ��� ����
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

    // �⺻ �޽��� �����Դϴ�:
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


// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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