#pragma once

#ifndef __DEFINE_ENGINEGRAPHIC_H_
#define __DEFINE_ENGINEGRAPHIC_H_

#include "ThirdParty/inc/DirectXTex.h"

#include "TSingleton.h"

class EngineGraphic : public TSingleton<EngineGraphic>
{
public:
	// delete function
	EngineGraphic(const EngineGraphic& _Other) = delete;
	EngineGraphic(EngineGraphic&& _Other) noexcept = delete;
	EngineGraphic& operator=(const EngineGraphic& _Other) = delete;
	EngineGraphic& operator=(EngineGraphic&& _Other) = delete;

	bool Initialize(HWND* _pHandle);

	// 사용했던 Direct 객체를 시스템에 반환
	void Release();

protected:

private:

};


#endif // !__DEFINE_ENGINEGRAPHIC_H_
