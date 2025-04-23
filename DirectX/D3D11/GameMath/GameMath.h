#pragma once

#ifndef __DEFINE_GAME_MATH_H
#define __DEFINE_GAME_MATH_H
#include <iostream>
#include <cassert>
#include <string>
#include <DirectXMath.h>

#define EXPERIENCE_MATH__ true
#if EXPERIENCE_MATH__
#define EXPERIENCE_MATH_

#endif // EXPERIENCE_MATH__


struct GameEngineMath
{
	// 두 값이 동일한 지에 대한 유무를 반환한다.
	static bool Equals(float _lhs, float _rhs)
	{
		// 두 값의 뺀 값이 앱실론(매우 작은 값)보다 작다면 상등하다고 판정
		return (_lhs - _rhs) < FLT_EPSILON;
	}

	static float D2R(float _Deg)
	{
		return DirectX::XMConvertToRadians(_Deg);
	}
	static float R2D(float _Rad)
	{
		return DirectX::XMConvertToDegrees(_Rad);
	}
};


// 가상 세계에서 사용될 벡터
struct float4
{
	// define variant 
public:
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 FRONT;
	static const float4 BACK;

public:
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 1.0f)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

	float4(const DirectX::XMVECTOR& _v)
		: DirectXVector(_v)
	{

	}

	float4(DirectX::XMVECTOR&& _v) noexcept
		: DirectXVector(_v)
	{

	}

	const float* GetArray() const
	{
		return &X;
	}

	union
	{
		DirectX::XMVECTOR DirectXVector;
		// 128비트 크기 단위로 연산을 수행한다.
		// 128비트에 float을 4개 적재해서 한 번에 계산
		// 성능상으로 3~4배 빠르다.
		float Arr[4] = {};
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
	};

	bool operator==(const float4& _Other) const
	{
		return DirectX::XMVector3Equal(DirectXVector, _Other.DirectXVector);
	}

	bool operator!=(const float4& _Other) const
	{
		return !operator==(_Other);
	}

	float4& operator*=(float _Scalar)
	{ 
		DirectXVector = DirectX::XMVectorScale(DirectXVector, _Scalar);
		return (*this);
	}

	float4& operator/=(float _Scalar)
	{ 
		DirectXVector = DirectX::XMVectorScale(DirectXVector, 1.0f / _Scalar);
		return (*this);
	}

	/* 각 항목이 0인 벡터를 반환합니다. */
	static float4 Zero()
	{
		return DirectX::XMVectorZero();
	}

	/* 각 항목이 1인 벡터를 반환합니다. */
	static float4 One()
	{
		return DirectX::XMVectorSplatOne();
	}

	/* 각 항목이 매개변수 값인 벡터를 반환합니다. */
	static float4 One(float _S)
	{
		return DirectX::XMVectorReplicate(_S);
	}

	// 벡터가 가리키는 선의 길이를 반환합니다.
	static float Length3D(const float4& _v)
	{
		float4 V = DirectX::XMVector3Length(_v.DirectXVector);
		return V.X;
	}

	float Length3D() const
	{
		return Length3D(*this);
	}

	// 정규화된 방향벡터를 반환합니다.
	static float4 Normalize(const float4& _v)
	{
		return DirectX::XMVector3Normalize(_v.DirectXVector);;
	}

	// 단일 벡터로 변환합니다.
	float4& Normalized()
	{
		(*this) = Normalize(*this);
		return *this;
	}

	// 내적을 수행합니다.
	// 내적은 방향 벡터에 대한 정사형
	// 결과값이 0일 경우, 방향 벡터에 대하여 수직
	// 결과값이 0보다 클 경우, 방향 벡터에 대하여 예각
	// 결과값이 0보다 작을 경우, 방향 벡터에 대하여 둔각
	static float Dot3D(const float4& _v1, const float4& _v2)
	{
		// const float Result = _v1.X * _v2.X + _v1.Y * _v2.Y + _v1.Z * _v2.Z;
		const float4 Result = DirectX::XMVector3Dot(_v1.DirectXVector, _v2.DirectXVector);
		return Result.X;
	}

	float Dot3D(const float4& _v) const
	{
		return Dot3D(*this, _v);
	}

	// 외적 
	// 흔히 가위 곱이라고 하며, 내적과 달리 3차원 곱에서만 정의된다.
	// 외적 시, 두 각에 대하여 직교인 다른 벡터가 나온다.
	static float4 Cross3D(const float4& _V1, const float4& _V2)
	{
		/*(_A.Y * _B.Z - _A.Z * _B.Y),
		(_A.Z * _B.X - _A.X * _B.Z),
		(_A.X * _B.Y - _A.Y * _B.X)*/

		const float4 Result = DirectX::XMVector3Cross(_V1.DirectXVector, _V2.DirectXVector);
		return Result.X;
	}
	const float4 Cross3D(const float4& _Other) const
	{
		return Cross3D(*this, _Other);
	}

#ifdef EXPERIENCE_MATH_
	static const float4 Orthogonal3D(const float4& _V)
	{
		return DirectX::XMVector3Orthogonal(_V.DirectXVector);
	}

	const float4 Orthogonal3D() const
	{
		return Orthogonal3D(*this);
	}

#endif // EXPERIENCE_MATH_

	// 두 벡터 사이 각도를 반환합니다.
	static float AngleBetwwenVectors3D(const float4& _V1, const float4& _V2)
	{
		const float4 Result{ DirectX::XMVector3AngleBetweenVectors(_V1.DirectXVector, _V2.DirectXVector) };
		return Result.X;
	}

	// 노말 벡터에 대한 직선의 평행선과 수직선을 반환합니다.
	static void ComponentsFromNormal3D(
		float4*       _pParallel,
		float4*       _pPerpendicular,
		const float4& _V,
		const float4& _Normal)
	{
		assert(nullptr != _pParallel && nullptr != _pPerpendicular);

		DirectX::XMVector3ComponentsFromNormal(
			&_pParallel->DirectXVector, 
			&_pPerpendicular->DirectXVector, 
			_V.DirectXVector, _Normal.DirectXVector);
	}

};

inline float4 operator+(const float4& _lhs, const float4& _rhs)
{
	const float4 Result{ DirectX::XMVectorAdd(_lhs.DirectXVector, _rhs.DirectXVector) };
	return Result;
}

inline float4 operator-(const float4& _lhs, const float4& _rhs)
{
	const float4 Result{ DirectX::XMVectorSubtract(_lhs.DirectXVector, _rhs.DirectXVector) };
	return Result;
}

inline float4 operator*(const float4& _lhs, float _rhs)
{
	const float4 Result{ DirectX::XMVectorScale(_lhs.DirectXVector, _rhs) };
	return Result;
}

inline float4 operator/(const float4& _lhs, float _rhs)
{
	const float4 Result{ DirectX::XMVectorScale(_lhs.DirectXVector, (1.0f / _rhs)) };
	return Result;
}

inline std::ostream& operator<<(std::ostream& _os, const float4& _Object)
{
	_os << "{ " << _Object.X << ", " << _Object.Y << ", " << _Object.Z << ", " << _Object.W << " }";
	return _os;
}


// 행렬: N개의 열과 N개의 행으로 이루어진다.
// 컴퓨터 공학에서 행렬은 벡터의 비례, 회전, 이동을 
// 기하학적 변환을 통해 간략하게 나타낼 수 있다.
// 
// 행렬은 쌍으로 이루며, NxN을 N차원이라고 하고, 
// 각 항목을 원소(Element) 또는 성분(Entry)이라고 한다.
// 행렬의 각 성분을 지칭할 때는 성분의 색인으로 지정하는 형태의 표현법을 사용한다.
// 
// 행이나 열이 하나일 경우, 각각 행벡터, 열벡터라고 칭하며,
// 백터 형태에서 행렬 형태로 사용될 수 있다.
// 행벡터, 열벡터는 이중 색인 대신 단일 색인으로 봐도 무방하다.

// 정방행렬 표기식: detA (단, A!=0) 
// 소행렬 표기식: (A^-)ij
//	- 특정 행과 열을 제거한 행렬
// 
// 역행렬은 정방행렬에 대한 곱으로 단위행렬이 되는 행렬이다.
// 역행렬이 존재하지 않을 경우 -> 특이행렬, 
//			존재할 경우 -> 가역행렬

class float4x4
{
public:
	static constexpr int MatrixXCount = 4;
	static constexpr int MatrixYCount = 4;

public:
	float4x4(const DirectX::XMMATRIX& _Mat = DirectX::XMMatrixIdentity())
		: DirectXMatrix(_Mat)
	{
	}

	float4x4(DirectX::XMMATRIX&& _Mat) noexcept
		: DirectXMatrix(_Mat)
	{
	}

	union
	{

		float Arr1D[MatrixXCount * MatrixYCount];
		float Arr2D[MatrixXCount][MatrixYCount];

		struct
		{
			float 
				_00, _01, _02, _03,
				_10, _11, _12, _13,
				_20, _21, _22, _23,
				_30, _31, _32, _33;
		};

		DirectX::XMMATRIX DirectXMatrix;
	};

	// 행렬의 전치
	// 각 행과 열의 구성을 교환한 것
	// 행과 열의 차원 또한 교환되어 진다.
	// ex) 1x4 -> 4x1
	// 표기 방식은 M^T
	static float4x4 Transpose(const float4x4& _pMatrix)
	{
		return DirectX::XMMatrixTranspose(_pMatrix.DirectXMatrix);
	}

	float4x4& Transposed()
	{
		// 대입 비용 아깝...
		(*this) = Transpose(*this);
		return *this;
	}

	const float4x4 T() const
	{
		return Transpose(*this);
	}

	// 단위행렬 
	// 행렬의 좌상에서 우하로 구성된 대각선으로 
	// 이루어진 항목이 1이고 나머지가 0인 정방행렬
	// 단위행렬에 대한 곱셈은 항등원 역할을 한다.
	// M*1(Iden) == M
	static float4x4 Identity()
	{
		return DirectX::XMMatrixIdentity();
	}

	void Identified()
	{
		(*this) = Identity();
	}

	static float4x4 Inverse(const float4x4& _Mat)
	{
		return DirectX::XMMatrixInverse(nullptr, _Mat.DirectXMatrix);
	}
};

/* 행렬에 대한 덧셈이나, 스칼라 곱은 각 성분별로 계산되어 진다. */

// 행렬에 대한 곱을 성립하기 위해서 lhs의 열과 rhs의 행의 수가 일치해야 한다.
// 예를 들어, A가 1x4인 행렬과 B가 4x3인 행렬일 경우, 
// A*B의 결과 값은 A의 i번째 행벡터 B의 j번째 열벡터의 내적이된다.
// 이로부터 만들어진 C행렬은 Cij가 된다.
// 
// 덧셈은 교환법칙이 성립되지만, 곱셈은 성립되지 않는다.
inline const float4x4 operator*(const float4x4& _lhs, const float4x4& _rhs)
{
	const float4x4 Result{ DirectX::XMMatrixMultiply(_lhs.DirectXMatrix, _rhs.DirectXMatrix) };
	return Result;
}

inline std::ostream& operator<<(std::ostream& _os, const float4x4& _Mat)
{
	static std::string Str;
	Str.clear();

	for (int i = 0; i < 16; i++)
	{
		Str += std::to_string(_Mat.Arr1D[i]);
		Str += ", ";

		if (i % 4 == 3)
		{
			Str += '\n';
		}
	}
	_os << Str;
	return _os;
}

#endif // !__DEFINE_GAME_MATH_H


