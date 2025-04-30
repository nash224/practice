#pragma once

#ifndef __DEFINE_HEADER_H_
#define __DEFINE_HEADER_H_

#include <WinUser.h>

#define safe_delete(x) if (nullptr != x) delete x; x = nullptr;

#define MessageBoxAssert(msg) MessageBox(0, msg, L"Error", MB_OK);
#define MessageBoxAssertReturn(msg) MessageBoxAssert(msg); return;

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

namespace engine
{
	namespace debug
	{
		inline void LeakCheck()
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}

		inline void OutputString(LPTSTR _tStr)
		{
			OutputDebugString(_tStr);
		}
	}
}

#endif

#endif // !__DEFINE_HEADER_H_
