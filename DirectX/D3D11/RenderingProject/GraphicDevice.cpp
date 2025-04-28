#include "GraphicDevice.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dxgi")

#if _DEBUG
#pragma comment(lib, "ThirdParty\\lib\\debug\\DirectXTex.lib")
#else
#pragma comment(lib, "ThirdParty\\lib\\release\\DirectXTex.lib")
#endif // DEBUG


using namespace DirectX;

bool GraphicDevice::CreateDevice()
{
	UINT CreateDeviceFlag = 0;

#if defined(DEBUG) || defined(_DEBUG) 
	CreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;

#endif // defined(DEBUG) || defined(_DEBUG) 

	D3D_FEATURE_LEVEL FeatureLevel;

	HRESULT hr = D3D11CreateDevice(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		0, 
		CreateDeviceFlag, 
		nullptr, 0, 
		D3D11_SDK_VERSION, 
		&mDevice, 
		&FeatureLevel, 
		&mDeviceContext);

	if (FAILED(hr))
	{
		MessageBoxAssert(L"D3D11CreateDevice Failed.");
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

}