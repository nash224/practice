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

	// D3D 디바이스 초기화
	HRESULT hr = D3D11CreateDevice(
		0,						  // 기본 어뎁터 사용
		D3D_DRIVER_TYPE_HARDWARE, // 렌더링 3차원 가속을 위한 표준 장치 생성
		0,						  // 소프트웨어 구동기 지정, D3D_DRIVER_TYPE_HARDWARE 선택 시, 기본 값 초기화
		createDeviceFlags,        // 추가적으로 생성할 장치
		0, 0,				      // d3d 프레임워크 지정, null 설정 시, 가용할 수 있는 프레임워크 중에서 가장 최신으로 지정
		D3D11_SDK_VERSION, 
		&md3dDevice,              // 생성된 장치를 포인터로 반환
		&featureLevel,            // 선택된 feature level 반환
		&md3dImmediateContext      // 장치 문맥 반환
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

	// MSAA 지원 검사
	UINT m4xMsaaQuality;
	md3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			4, &m4xMsaaQuality);

	assert(0 < m4xMsaaQuality);
	const bool mEnable4xMsaa = 0 < m4xMsaaQuality;

	// 스왑체인 특성 정의
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};
	// 백버퍼의 속성을 BufferDesc에 서술
	SwapDesc.BufferDesc.Width                   = engine::window::WinSize::Width;	    // 화면의 넓이
	SwapDesc.BufferDesc.Height                  = engine::window::WinSize::Height;      // 화면의 높이
	SwapDesc.BufferDesc.RefreshRate.Numerator   = 60;                                   // 디스플레이 갱신율
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1; 
	SwapDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;           // 백버퍼 픽셀 형식
	SwapDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // 모름
	SwapDesc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;        // 화면 크기 변환 시, 스케일 모드 지정

	if (mEnable4xMsaa)
	{
		SwapDesc.SampleDesc.Count   = 4;					// 샘플링 개수
		SwapDesc.SampleDesc.Quality = m4xMsaaQuality - 1;	// 샘플링 품질 수준
	}
	else
	{
		SwapDesc.SampleDesc.Count   = 1;
		SwapDesc.SampleDesc.Quality = 0;
	}

	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 버퍼의 용도, 백버퍼를 렌더링에 사용할 것이다.
	SwapDesc.BufferCount = 1;	                            // 백버퍼 수 1개 -> 더블 버퍼링,  2개 -> 삼중 버퍼링
	SwapDesc.OutputWindow = (*_pHandle);                    // 출력할 화면
	SwapDesc.Windowed    = true;                            // 창 모드 유무, false -> 전체화면 모드
	SwapDesc.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;        // buffer가 교체되는 방법 지정, 
													        // discard로 초기화할 경우, 가장 성능 좋은 것으로 지정
	SwapDesc.Flags       = 0;                               // 추가 플래그


	// DXGI는 다른 그래픽 프레임워크에서 독립적으로 사용할 수 있는 
	// 모듈형식으로 구현되어 개별적으로 API를 사용할 수 있게 지원한다.
	// 
	// 스왑체인 객체를 얻기 위해, 차례대로 COM의 질의를 거친다.
	IDXGIDevice* dxgiDevice = 0;
	assert(S_OK == md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// 어뎁터는 컴퓨터의 하드웨어 및 소프트웨어를 추상화한 객체
	// 내부에 GPU, 메모리 등을 포함하는 디스플레이 서브 시스템의 정보를 들고 있다.
	IDXGIAdapter* dxgiAdapter = 0;
	assert(S_OK == dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// 펙토리는 dxgi 객체를 생성하는 메서드를 포함한다.
	IDXGIFactory* dxgiFactory = 0;
	assert(S_OK == dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	IDXGISwapChain* mSwapChain;
	assert(S_OK == dxgiFactory->CreateSwapChain(md3dDevice, &SwapDesc, &mSwapChain));

	// 사용을 끝낸 COM 객체는 정리한다. (내부 참조 카운터 감소)
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();


	// 렌더타겟뷰는 이미지 버퍼를 수정할 수 있는 권한
	// 렌더타켓뷰 생성하고 병합기에 바인딩
	ID3D11RenderTargetView* mRTV;
	ID3D11Texture2D* backBuffer = 0;

	// 스왑체인에 존재하는 백버퍼를 가져온다.
	assert(S_OK	== mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	// 버퍼에서 RTV 생성
	md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRTV);

	// 버퍼의 참조카운터 반환
	backBuffer->Release();


	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width                = engine::window::WinSize::Width; // 깊이 버퍼도 화면의 크기만큼 설정
	depthStencilDesc.Height               = engine::window::WinSize::Height; 
	depthStencilDesc.MipLevels            = 1;                              // 밉레벨은 렌더링 속도를 향상시키기 위해 
			                                                                //미리 축소된 텍스처를 배열로 저장하고, 
			                                                                // 거리에 따라 축소된 텍스처를 사용하는 기법
	depthStencilDesc.ArraySize            = 1;
	depthStencilDesc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;  // 텍셀의 형식

	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;						// 샘플링 개수
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;	// 샘플링 품질 수준
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;      // 텍스처를 gpu에서만 읽기/쓰기 수행, 디폴트 값
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL; // 버퍼에 stencil을 포함하겠다.
	depthStencilDesc.CPUAccessFlags = 0;                        // cpu 접근 허용 x
	depthStencilDesc.MiscFlags      = 0; 

	ID3D11Texture2D* mDepthStencilBuffer;
	// 깊이-스탠실을 수정할 권한
	ID3D11DepthStencilView* mDepthStencilView;

	assert(S_OK == md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	assert(S_OK == md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


	// 병합기에 RTV 바인딩
	md3dImmediateContext->OMSetRenderTargets(1, &mRTV, mDepthStencilView);

	// 뷰포트도 병합기에 바인딩
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
