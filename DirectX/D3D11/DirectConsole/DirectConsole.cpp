﻿// DirectConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#pragma comment (lib, "GameMath.lib")

#include "GameMath/GameMath.h"

int main()
{
	float4 PosA;


	std::cout << "Determinant Mat" << DirectX::XMMatrixDeterminant(float4x4::Identity().DirectXMatrix) << '\n';
	std::cout << float4x4::Inverse(float4x4::Identity());

	std::cout << float4::UP * DirectX::XMMatrixRotationAxis(float4::RIGHT.DirectXVector, 90.0f);
}
