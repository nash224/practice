#pragma once

#ifndef __DEFINE_ENGINEGRAPHIC_H_
#define __DEFINE_ENGINEGRAPHIC_H_

#include "ThirdParty/inc/DirectXTex.h"

#include "TSingleton.h"

class EngineGraphic
{
public:
	EngineGraphic();
	~EngineGraphic();

	// delete function
	EngineGraphic(const EngineGraphic& _Other) = delete;
	EngineGraphic(EngineGraphic&& _Other) noexcept = delete;
	EngineGraphic& operator=(const EngineGraphic& _Other) = delete;
	EngineGraphic& operator=(EngineGraphic&& _Other) = delete;

	bool Init(HWND _pHandle);
	void OnResize();
	void Release();

protected:

private:
	UINT m4xMsaaQuality = 0;
	bool mEnable4xMsaa = false;

	ID3D11Device*           md3dDevice = nullptr;           // 그래픽 자원할당 관리자
	ID3D11DeviceContext*    md3dImmediateContext = nullptr; // 렌더 파이프라인 관리자
	IDXGISwapChain*         mSwapChain = nullptr;           // 스왑체인 
	ID3D11RenderTargetView* mRTV = nullptr;                 // 버퍼의 렌더링 권한
	ID3D11Texture2D*        mDepthStencilBuffer = nullptr;  // 깊이-스탠실 텍스처 버퍼
	ID3D11DepthStencilView* mDepthStencilView = nullptr;    // 깊이-스탠실을 수정할 권한
	D3D11_VIEWPORT			mViewPort;

};


#endif // !__DEFINE_ENGINEGRAPHIC_H_
