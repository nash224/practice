#pragma once

#ifndef __DEFINE_INT2_H
#define __DEFINE_INT2_H


struct Int2
{
public:
	Int2(int _X = 0, int _Y = 0)
		: x(_X)
		, y(_Y)
	{

	}

	Int2& operator+=(const Int2& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		return *this;
	}

	int x, y;
};

inline Int2 operator+(const Int2& _lhs, const Int2& _rhs)
{
	return Int2(_lhs.x + _rhs.x, _lhs.y + _rhs.y);
}

#endif // !__DEFINE_INT2_H
