#pragma once

#ifndef __DEFINE_D3DUTIL_H_
#define __DEFINE_D3DUTIL_H_

#include <d3d11.h>
#include <winnt.h>

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
	#define HR(x)                                           \
	{                                                       \
		HRESULT hr = (x);                                   \
		if(FAILED(hr))                                      \
		{                                                   \
			LPWSTR msg;                                     \
			                                                \
			FormatMessage(                                  \
				FORMAT_MESSAGE_FROM_SYSTEM |                \
				FORMAT_MESSAGE_ALLOCATE_BUFFER,             \
				nullptr, hr,                                \
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  \
				(LPTSTR)&msg,                               \
				0, nullptr);                                \
			MessageBox(NULL, msg, L"Error", MB_OK);         \
			LocalFree(msg);                                 \
		}                                                   \
	}
	#endif // !HR
#else
#ifndef HR
	#define HR(x) (x)
	#endif // !HR

#endif // defined(DEBUG) | defined(_DEBUG)


//---------------------------------------------------------------------------------------
// Macro for releasing COM object.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){x->Release(); x = nullptr; }}



#endif // !__DEFINE_D3DUTIL_H_
