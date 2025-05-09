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

// �׷��� �������� ���� ������ ���� ó���� ����Ѵ�.

class ApplicationClass
{
public:
	ApplicationClass();
	~ApplicationClass();


	/**
	 * @brief		Initialize	���ø����̼� �ʱ�ȭ �Լ�
	 *
	 * @param		screenWidth		ȭ�� ���� ũ��
	 * @param		screenHieght	ȭ�� ���� ũ��
	 * @param		hwnd			����ȭ�� �ڵ�
	 *
	 * @return		bool		���������� �ʱ�ȭ�ߴٸ� true
	 *
	 * @warning		null
	 */
	bool Initialize(int screenWidth, int screenHieght, HWND hwnd);
	void Shutdown();
	bool Frame();

private:
	bool Render();

};

#endif // !__DEFINE_APLLICATIONCLASS_H_
