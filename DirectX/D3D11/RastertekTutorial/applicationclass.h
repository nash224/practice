//***************************************************************************************
// apllicationclass.h by nash224 Visual Studio (C++) 2025 All Rights Reserved.
//***************************************************************************************

#pragma once

#ifndef __DEFINE_APLLICATIONCLASS_H_
#define __DEFINE_APLLICATIONCLASS_H_


//---------------------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------------------

#include <windows.h>

//---------------------------------------------------------------------------------------
// GLOBALS
//---------------------------------------------------------------------------------------

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;


//---------------------------------------------------------------------------------------
// Class name: ApplicationClass
//---------------------------------------------------------------------------------------

// 그래픽 렌더링과 게임 로직에 대한 처리를 당담한다.

class ApplicationClass
{
public:
	ApplicationClass();
	~ApplicationClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

};

#endif // !__DEFINE_APLLICATIONCLASS_H_
