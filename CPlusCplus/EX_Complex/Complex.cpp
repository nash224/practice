#include "Complex.h"

Complex::~Complex()
{

}


Complex Complex::operator+(const Complex& _Other) const
{
	return (mReal + _Other.mReal, mImg + _Other.mImg);
}

Complex Complex::operator-(const Complex& _Other) const
{
	return (mReal - _Other.mReal, mImg - _Other.mImg);
}

Complex Complex::operator*(const Complex& _Other) const
{
	return (mReal * _Other.mReal - mImg * _Other.mImg, mReal * _Other.mImg, mImg * _Other.mReal);
}

Complex Complex::operator/(const Complex& _Other) const
{
	return ((mReal * _Other.mReal + mImg * _Other.mImg) / (_Other.mReal * _Other.mReal + _Other.mImg * _Other.mImg)
		, (mImg * _Other.mReal - mReal * _Other.mImg) / (_Other.mReal * _Other.mReal + _Other.mImg * _Other.mImg));
}


Complex& Complex::operator+=(const Complex& _Other)
{
	mImg += _Other.mImg;
	mReal += _Other.mReal;
	return (*this);
}

Complex& Complex::operator-=(const Complex& _Other)
{
	mImg -= _Other.mImg;
	mReal -= _Other.mReal;
	return (*this);
}

Complex& Complex::operator*=(const Complex& _Other)
{
	// 최적화 할 수는 있지만, 함수의 용도를 학습하기 위한 코드이므로 최적화 수행 x
	(*this) = (*this) * _Other;
	return (*this);
}

Complex& Complex::operator/=(const Complex& _Other)
{
	// 최적화 할 수는 있지만, 함수의 용도를 학습하기 위한 코드이므로 최적화 수행 x
	(*this) = (*this) / _Other;
	return (*this);
}


