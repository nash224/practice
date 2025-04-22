#pragma once

#ifndef __DEFINE_GAME_MATH_H
#define __DEFINE_GAME_MATH_H
#include <iostream>
#include <cassert>
#include <DirectXMath.h>

#define EXPERIENCE_MATH__ true
#if EXPERIENCE_MATH__
#define EXPERIENCE_MATH_

#endif // EXPERIENCE_MATH__


struct GameEngineMath
{
	// �� ���� ������ ���� ���� ������ ��ȯ�Ѵ�.
	static bool Equals(float _lhs, float _rhs)
	{
		// �� ���� �� ���� �۽Ƿ�(�ſ� ���� ��)���� �۴ٸ� ����ϴٰ� ����
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


// ���� ���迡�� ���� ����
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
		// 128��Ʈ ũ�� ������ ������ �����Ѵ�.
		// 128��Ʈ�� float�� 4�� �����ؼ� �� ���� ���
		// ���ɻ����� 3~4�� ������.
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

	/* �� �׸��� 0�� ���͸� ��ȯ�մϴ�. */
	static float4 Zero()
	{
		return DirectX::XMVectorZero();
	}

	/* �� �׸��� 1�� ���͸� ��ȯ�մϴ�. */
	static float4 One()
	{
		return DirectX::XMVectorSplatOne();
	}

	/* �� �׸��� �Ű����� ���� ���͸� ��ȯ�մϴ�. */
	static float4 One(float _S)
	{
		return DirectX::XMVectorReplicate(_S);
	}

	// ���Ͱ� ����Ű�� ���� ���̸� ��ȯ�մϴ�.
	static float Length3D(const float4& _v)
	{
		float4 V = DirectX::XMVector3Length(_v.DirectXVector);
		return V.X;
	}

	float Length3D() const
	{
		return Length3D(*this);
	}

	// ����ȭ�� ���⺤�͸� ��ȯ�մϴ�.
	static float4 Normalize(const float4& _v)
	{
		return DirectX::XMVector3Normalize(_v.DirectXVector);;
	}

	// ���� ���ͷ� ��ȯ�մϴ�.
	float4& Normalized()
	{
		(*this) = Normalize(*this);
		return *this;
	}

	// ������ �����մϴ�.
	// ������ ���� ���Ϳ� ���� ������
	// ������� 0�� ���, ���� ���Ϳ� ���Ͽ� ����
	// ������� 0���� Ŭ ���, ���� ���Ϳ� ���Ͽ� ����
	// ������� 0���� ���� ���, ���� ���Ϳ� ���Ͽ� �а�
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

	// ���� 
	// ���� ���� ���̶�� �ϸ�, ������ �޸� 3���� �������� ���ǵȴ�.
	// ���� ��, �� ���� ���Ͽ� ������ �ٸ� ���Ͱ� ���´�.
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

	// �� ���� ���� ������ ��ȯ�մϴ�.
	static float AngleBetwwenVectors3D(const float4& _V1, const float4& _V2)
	{
		const float4 Result{ DirectX::XMVector3AngleBetweenVectors(_V1.DirectXVector, _V2.DirectXVector) };
		return Result.X;
	}

	// �븻 ���Ϳ� ���� ������ ���༱�� �������� ��ȯ�մϴ�.
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


// ���: N���� ���� N���� ������ �̷������.
// ��ǻ�� ���п��� ����� ������ ���, ȸ��, �̵��� 
// �������� ��ȯ�� ���� �����ϰ� ��Ÿ�� �� �ִ�.
// 
// ����� ������ �̷��, NxN�� N�����̶�� �ϰ�, 
// �� �׸��� ����(Element) �Ǵ� ����(Entry)�̶�� �Ѵ�.
// ����� �� ������ ��Ī�� ���� ������ �������� �����ϴ� ������ ǥ������ ����Ѵ�.
// 
// ���̳� ���� �ϳ��� ���, ���� �຤��, �����Ͷ�� Ī�ϸ�,
// ���� ���¿��� ��� ���·� ���� �� �ִ�.
// �຤��, �����ʹ� ���� ���� ��� ���� �������� ���� �����ϴ�.

class Matrix4x4
{
public:


};

#endif // !__DEFINE_GAME_MATH_H


