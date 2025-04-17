#pragma once

#ifndef __DEFINE_COMPLEX_H
#define __DEFINE_COMPLEX_H

class Complex
{
	using data_type = double;

public:
	Complex(data_type Real = 0.0, data_type Img = 0.0)
		: mReal(Real)
		, mImg(Img)
	{

	}

	Complex(const Complex& _Other) = default;

	~Complex();

	Complex& operator=(const Complex& _Other)
	{
		mImg = _Other.mImg;
		mReal = _Other.mReal;
		return (*this);
	}

	// Release 모드에서 RVO 가 적용된다고 가정
	// 호출자에서 리턴 타입 임시 객체 생성
	Complex operator+(const Complex& _Other) const;
	Complex operator-(const Complex& _Other) const;
	Complex operator*(const Complex& _Other) const;
	Complex operator/(const Complex& _Other) const;

	Complex& operator+=(const Complex& _Other);
	Complex& operator-=(const Complex& _Other);
	Complex& operator*=(const Complex& _Other);
	Complex& operator/=(const Complex& _Other);

protected:

private:
	data_type mImg;
	data_type mReal;

};

#endif // !__DEFINE_COMPLEX_H

