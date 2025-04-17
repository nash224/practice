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
	// ����ȭ �� ���� ������, �Լ��� �뵵�� �н��ϱ� ���� �ڵ��̹Ƿ� ����ȭ ���� x
	(*this) = (*this) * _Other;
	return (*this);
}

Complex& Complex::operator/=(const Complex& _Other)
{
	// ����ȭ �� ���� ������, �Լ��� �뵵�� �н��ϱ� ���� �ڵ��̹Ƿ� ����ȭ ���� x
	(*this) = (*this) / _Other;
	return (*this);
}


