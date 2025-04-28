#pragma once

#ifndef __DEFINE_GRAPHICDEVICE_H_
#define __DEFINE_GRAPHICDEVICE_H_

#include "ThirdParty\\inc\\DirectXTex.h"

class GraphicDevice
{
public:
	// constructor & destructor
	GraphicDevice() {}
	~GraphicDevice() {}

	// delete function
	GraphicDevice(const GraphicDevice& _Other) = delete;
	GraphicDevice(GraphicDevice&& _Other) noexcept = delete;
	GraphicDevice& operator=(const GraphicDevice& _Other) = delete;
	GraphicDevice& operator=(GraphicDevice&& _Other) = delete;

	bool CreateDevice();

protected:

private:
	ID3D11Device* mDevice = nullptr;
	ID3D11DeviceContext* mDeviceContext = nullptr;

};


#endif // !__DEFINE_GRAPHICDEVICE_H_
