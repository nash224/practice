#include "EngineGraphic.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dxgi")

#if _DEBUG
#pragma comment(lib, "ThirdParty\\lib\\debug\\DirectXTexd.lib")
#else
#pragma comment(lib, "ThirdParty\\lib\\release\\DirectXTex.lib")
#endif // DEBUG

#include <cassert>
#include "Header.h"
#include "Constant.h"

using namespace DirectX;

bool EngineGraphic::Initialize(HWND* _pHandle)
{
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;

	// D3D ����̽� �ʱ�ȭ
	HRESULT hr = D3D11CreateDevice(
		0,						  // �⺻ ��� ���
		D3D_DRIVER_TYPE_HARDWARE, // ������ 3���� ������ ���� ǥ�� ��ġ ����
		0,						  // ����Ʈ���� ������ ����, D3D_DRIVER_TYPE_HARDWARE ���� ��, �⺻ �� �ʱ�ȭ
		createDeviceFlags,        // �߰������� ������ ��ġ
		0, 0,				      // d3d �����ӿ�ũ ����, null ���� ��, ������ �� �ִ� �����ӿ�ũ �߿��� ���� �ֽ����� ����
		D3D11_SDK_VERSION, 
		&md3dDevice,              // ������ ��ġ�� �����ͷ� ��ȯ
		&featureLevel,            // ���õ� feature level ��ȯ
		&md3dImmediateContext      // ��ġ ���� ��ȯ
	);

	if (FAILED(hr))
	{
		MessageBoxAssert(L"D3D11CreateDevice Failed.");
		return false;
	}

	if ((featureLevel != D3D_FEATURE_LEVEL_11_1) 
		&& (featureLevel != D3D_FEATURE_LEVEL_11_0))
	{
		MessageBoxAssert(L"Direct3D Feature Level 11 unsupported.");
		return false;
	}

	// MSAA ���� �˻�
	UINT m4xMsaaQuality;
	md3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			4, &m4xMsaaQuality);

	assert(0 < m4xMsaaQuality);
	const bool mEnable4xMsaa = 0 < m4xMsaaQuality;

	// ����ü�� Ư�� ����
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	// ������� �Ӽ��� BufferDesc�� ����
	SwapDesc.BufferDesc.Width                   = engine::window::WinSize::Width;	    // ȭ���� ����
	SwapDesc.BufferDesc.Height                  = engine::window::WinSize::Height;      // ȭ���� ����
	SwapDesc.BufferDesc.RefreshRate.Numerator   = 60;                                   // ���÷��� ������
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1; 
	SwapDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;           // ����� �ȼ� ����
	SwapDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ��
	SwapDesc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;        // ȭ�� ũ�� ��ȯ ��, ������ ��� ����

	if (mEnable4xMsaa)
	{
		SwapDesc.SampleDesc.Count   = 4;					// ���ø� ����
		SwapDesc.SampleDesc.Quality = m4xMsaaQuality - 1;	// ���ø� ǰ�� ����
	}
	else
	{
		SwapDesc.SampleDesc.Count   = 1;
		SwapDesc.SampleDesc.Quality = 0;
	}

	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// ������ �뵵, ����۸� �������� ����� ���̴�.
	SwapDesc.BufferCount = 1;	                            // ����� �� 1�� -> ���� ���۸�,  2�� -> ���� ���۸�
	SwapDesc.OutputWindow = (*_pHandle);                    // ����� ȭ��
	SwapDesc.Windowed    = true;                            // â ��� ����, false -> ��üȭ�� ���
	SwapDesc.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;        // buffer�� ��ü�Ǵ� ��� ����, 
													        // discard�� �ʱ�ȭ�� ���, ���� ���� ���� ������ ����
	SwapDesc.Flags       = 0;                               // �߰� �÷���


	// DXGI�� �ٸ� �׷��� �����ӿ�ũ���� ���������� ����� �� �ִ� 
	// ����������� �����Ǿ� ���������� API�� ����� �� �ְ� �����Ѵ�.
	// 
	// ����ü�� ��ü�� ��� ����, ���ʴ�� COM�� ���Ǹ� ��ģ��.
	IDXGIDevice* dxgiDevice = 0;
	assert(S_OK == md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// ��ʹ� ��ǻ���� �ϵ���� �� ����Ʈ��� �߻�ȭ�� ��ü
	// ���ο� GPU, �޸� ���� �����ϴ� ���÷��� ���� �ý����� ������ ��� �ִ�.
	IDXGIAdapter* dxgiAdapter = 0;
	assert(S_OK == dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// ���丮�� dxgi ��ü�� �����ϴ� �޼��带 �����Ѵ�.
	IDXGIFactory* dxgiFactory = 0;
	assert(S_OK == dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	IDXGISwapChain* mSwapChain;
	assert(S_OK == dxgiFactory->CreateSwapChain(md3dDevice, &SwapDesc, &mSwapChain));

	// ����� ���� COM ��ü�� �����Ѵ�. (���� ���� ī���� ����)
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();


	// ����Ÿ�ٺ�� �̹��� ���۸� ������ �� �ִ� ����
	// ����Ÿ�Ϻ� �����ϰ� ���ձ⿡ ���ε�
	ID3D11RenderTargetView* mRTV;
	ID3D11Texture2D* backBuffer = 0;

	// ����ü�ο� �����ϴ� ����۸� �����´�.
	assert(S_OK	== mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	// ���ۿ��� RTV ����
	md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRTV);

	// ������ ����ī���� ��ȯ
	backBuffer->Release();


	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width                = engine::window::WinSize::Width; // ���� ���۵� ȭ���� ũ�⸸ŭ ����
	depthStencilDesc.Height               = engine::window::WinSize::Height; 
	depthStencilDesc.MipLevels            = 1;                              // �ӷ����� ������ �ӵ��� ����Ű�� ���� 
			                                                                //�̸� ��ҵ� �ؽ�ó�� �迭�� �����ϰ�, 
			                                                                // �Ÿ��� ���� ��ҵ� �ؽ�ó�� ����ϴ� ���
	depthStencilDesc.ArraySize            = 1;
	depthStencilDesc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;  // �ؼ��� ����

	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;						// ���ø� ����
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;	// ���ø� ǰ�� ����
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;      // �ؽ�ó�� gpu������ �б�/���� ����, ����Ʈ ��
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL; // ���ۿ� stencil�� �����ϰڴ�.
	depthStencilDesc.CPUAccessFlags = 0;                        // cpu ���� ��� x
	depthStencilDesc.MiscFlags      = 0; 

	ID3D11Texture2D* mDepthStencilBuffer;
	// ����-���Ľ��� ������ ����
	ID3D11DepthStencilView* mDepthStencilView;

	assert(S_OK == md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	assert(S_OK == md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


	// ���ձ⿡ RTV ���ε�
	md3dImmediateContext->OMSetRenderTargets(1, &mRTV, mDepthStencilView);

	// ����Ʈ�� ���ձ⿡ ���ε�
	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = static_cast<float>(engine::window::WinPos::XPos);
	vp.TopLeftY = static_cast<float>(engine::window::WinPos::YPos);
	vp.Width = static_cast<float>(engine::window::WinSize::Width);
	vp.Height = static_cast<float>(engine::window::WinSize::Height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	md3dImmediateContext->RSSetViewports(1, &vp);

	md3dDevice->Release();
	md3dImmediateContext->Release();
	mSwapChain->Release();
	mRTV->Release();
	mDepthStencilBuffer->Release();
	mDepthStencilView->Release();

	return true;
}

void EngineGraphic::Release()
{
}
