// DirectXProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#pragma once  

#include "framework.h"
#include "EngineCore.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	EngineCore::EngineStart(hInstance);

    return 0;
}

