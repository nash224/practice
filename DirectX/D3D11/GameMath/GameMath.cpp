#include "GameMath.h"

#if _CONSOLE
class VertifyCPUInitializer
{
public:
	VertifyCPUInitializer()
	{
		if (false == DirectX::XMVerifyCPUSupport())
		{
			std::cout << "DirectX lib�� �����ϴ� ����̽��� ã�� ���߽��ϴ�.\n";
		}
	}
};

VertifyCPUInitializer Instance;

#endif // _CONSOLE


const float4 float4::RIGHT = float4{1.0f, 0.0f, 0.0f};
const float4 float4::UP    = float4{0.0f, 1.0f, 0.0f};
const float4 float4::FRONT = float4{0.0f, 0.0f, 1.0f};
const float4 float4::BACK = float4{0.0f, 0.0f, -1.0f};
