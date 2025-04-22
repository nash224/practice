#include "GameMath.h"

#if _CONSOLE
class VertifyCPUInitializer
{
public:
	VertifyCPUInitializer()
	{
		if (false == DirectX::XMVerifyCPUSupport())
		{
			std::cout << "DirectX lib를 지원하는 디바이스를 찾지 못했습니다.\n";
		}
	}
};

VertifyCPUInitializer Instance;

#endif // _CONSOLE


const float4 float4::RIGHT = float4{1.0f, 0.0f, 0.0f};
const float4 float4::UP    = float4{0.0f, 1.0f, 0.0f};
const float4 float4::FRONT = float4{0.0f, 0.0f, 1.0f};
const float4 float4::BACK = float4{0.0f, 0.0f, -1.0f};
