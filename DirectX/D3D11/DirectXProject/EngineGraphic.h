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

	ID3D11Device*           md3dDevice = nullptr;           // �׷��� �ڿ��Ҵ� ������
	ID3D11DeviceContext*    md3dImmediateContext = nullptr; // ���� ���������� ������
	IDXGISwapChain*         mSwapChain = nullptr;           // ����ü�� 
	ID3D11RenderTargetView* mRTV = nullptr;                 // ������ ������ ����
	ID3D11Texture2D*        mDepthStencilBuffer = nullptr;  // ����-���Ľ� �ؽ�ó ����
	ID3D11DepthStencilView* mDepthStencilView = nullptr;    // ����-���Ľ��� ������ ����
	D3D11_VIEWPORT			mViewPort;

};


#endif // !__DEFINE_ENGINEGRAPHIC_H_
