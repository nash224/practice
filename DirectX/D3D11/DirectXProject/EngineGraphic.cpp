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
#include "D3DUtil.h"
#include "Constant.h"

#include "EngineWindow.h"
#include "EngineCore.h"

static constexpr int BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

using namespace DirectX;

EngineGraphic::EngineGraphic()
{
	ZeroMemory(&mViewPort, sizeof(D3D11_VIEWPORT));
}

EngineGraphic::~EngineGraphic()
{
	Release();
}

bool EngineGraphic::Init(HWND _pHandle)
{
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;

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
	HR(md3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			4, &m4xMsaaQuality));

	mEnable4xMsaa = (0 < m4xMsaaQuality);

	// ����ü�� ����
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	// ����� ����
	SwapDesc.BufferDesc.Width                   = engine::window::WinSize::Width;	    // ȭ���� ����
	SwapDesc.BufferDesc.Height                  = engine::window::WinSize::Height;      // ȭ���� ����
	SwapDesc.BufferDesc.RefreshRate.Numerator   = 60;                                   // ���÷��� ������
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1; 
	SwapDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;           // ����� �ȼ� ����
	SwapDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ��
	SwapDesc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;        // ȭ�� ũ�� ��ȯ ��, ������ ��� ����

	// Enable 4x MSAA?
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
	SwapDesc.OutputWindow = (_pHandle);                     // ����� ȭ��
	SwapDesc.Windowed    = true;                            // â ��� ����, false -> ��üȭ�� ���
	SwapDesc.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;        // buffer�� ��ü�Ǵ� ��� ����, 
													        // discard�� �ʱ�ȭ�� ���, ���� ���� ���� ������ ����
	SwapDesc.Flags       = 0;                               // �߰� �÷���


	// DXGI�� �ٸ� �׷��� �����ӿ�ũ���� ���������� ����� �� �ִ� 
	// ����������� �����Ǿ� ���������� API�� ����� �� �ְ� �����Ѵ�.
	// 
	// ����ü�� ��ü�� ��� ����, ���ʴ�� COM�� ���Ǹ� ��ģ��.
	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// ��ʹ� ��ǻ���� �ϵ���� �� ����Ʈ��� �߻�ȭ�� ��ü
	// ���ο� GPU, �޸� ���� �����ϴ� ���÷��� ���� �ý����� ������ ��� �ִ�.
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// ���丮�� dxgi ��ü�� �����ϴ� �޼��带 �����Ѵ�.
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(md3dDevice, &SwapDesc, &mSwapChain));
	HR(dxgiFactory->MakeWindowAssociation(_pHandle, DXGI_MWA_NO_ALT_ENTER));

	// ����� ���� COM ��ü�� �����Ѵ�. (���� ���� ī���� ����)
	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	OnResize();

	return true;
}

void EngineGraphic::OnResize()
{
	assert(md3dImmediateContext);
	assert(md3dDevice);
	assert(mSwapChain);

	ReleaseCOM(mDepthStencilBuffer);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mRTV);

	const WinSize& Size = EngineWindow::GetWindowSize();
	HR(mSwapChain->ResizeBuffers(1, Size.Width, Size.Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0))

	// ����Ÿ�ٺ�� �̹��� ���۸� ������ �� �ִ� ����
	// ����Ÿ�Ϻ� �����ϰ� ���ձ⿡ ���ε�
	ID3D11Texture2D* backBuffer = nullptr;

	// ����ü�ο� �����ϴ� ����۸� �����´�.
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	assert(backBuffer);
	// ���ۿ��� RTV ����
	HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRTV));

	// ������ ����ī���� ��ȯ
	ReleaseCOM(backBuffer);

	// ����-���ٽ� ���� ����
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = engine::window::WinSize::Width; // ���� ���۵� ȭ���� ũ�⸸ŭ ����
	depthStencilDesc.Height = engine::window::WinSize::Height;
	depthStencilDesc.MipLevels = 1;                              // �ӷ����� ������ �ӵ��� ����Ű�� ���� 
	//�̸� ��ҵ� �ؽ�ó�� �迭�� �����ϰ�, 
	// �Ÿ��� ���� ��ҵ� �ؽ�ó�� ����ϴ� ���
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;  // �ؼ��� ����

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

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;      // �ؽ�ó�� gpu������ �б�/���� ����, ����Ʈ ��
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // ���ۿ� stencil�� �����ϰڴ�.
	depthStencilDesc.CPUAccessFlags = 0;                        // cpu ���� ��� x
	depthStencilDesc.MiscFlags = 0;

	HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));

	// ���ձ⿡ RTV ���ε�
	md3dImmediateContext->OMSetRenderTargets(1, &mRTV, mDepthStencilView);

	// ����Ʈ�� ���ձ⿡ ���ε�

	const WinSize& WinScale = EngineCore::GetWindowSize();
	const WinPos& WinPos = EngineCore::GetWindowPos();

	mViewPort.TopLeftX = static_cast<float>(WinPos.X);
	mViewPort.TopLeftY = static_cast<float>(WinPos.Y);
	mViewPort.Width    = static_cast<float>(WinScale.Width);
	mViewPort.Height   = static_cast<float>(WinScale.Height);

	mViewPort.TopLeftX = 100.0f;
	mViewPort.TopLeftY = 100.0f;
	mViewPort.Width    = 500.0f;
	mViewPort.Height   = 400.0f;
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;

	md3dImmediateContext->RSSetViewports(1, &mViewPort);
}


void EngineGraphic::Release()
{
	ReleaseCOM(mSwapChain);
	ReleaseCOM(mRTV);
	ReleaseCOM(mDepthStencilBuffer);
	ReleaseCOM(mDepthStencilView);

	if (nullptr != md3dImmediateContext)
	{
		md3dImmediateContext->ClearState();
	}
	ReleaseCOM(md3dImmediateContext);
	ReleaseCOM(md3dDevice);
}
