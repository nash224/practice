#include "String.h"
#include <stdexcept>

my_std::string::string()
	: mSize(0)
	, mCapacity(0)
	, mPtr(nullptr)
{
}

my_std::string::string(const_pointer _Str)
{
	const size_type Len = strlen(_Str);
	_Realloc(Len);
	mSize = Len;
	memcpy_s(mPtr, Len + 1, _Str, Len + 1);
}

my_std::string::string(const string& _Str)
{
	_Alloc(_Str.capacity());
	mSize = _Str.size();
	memcpy_s(mPtr, mSize + 1, _Str.c_str(), _Str.size() + 1);
}

my_std::string::string(string&& _Str) noexcept
{
	mSize = _Str.size();
	mCapacity = _Str.capacity();
	mPtr = _Str.mPtr;
	_Str.mPtr = nullptr;
}

my_std::string& my_std::string::operator=(const string& _Other)
{
	_Realloc(_Other.capacity());
	mSize = _Other.size();
	memcpy_s(mPtr, mSize, _Other.mPtr, _Other.mSize);
	return (*this);
}

my_std::string& my_std::string::operator=(string&& _Other) noexcept
{
	mSize = _Other.size();
	mCapacity = _Other.capacity();
	mPtr = _Other.mPtr;
	_Other.mPtr = nullptr;

	return (*this);
}

my_std::string::~string()
{
	_Destroy();
}

my_std::string& my_std::string::operator=(const_pointer _Str)
{
	const size_type Len = strlen(_Str);
	_Realloc(Len);
	mSize = Len;
	memcpy_s(mPtr, mCapacity + 1, _Str, Len + 1);
	return *this;
}

my_std::string& my_std::string::operator+=(const_pointer _Str)
{
	Append(_Str);
	return (*this);
}

my_std::string& my_std::string::operator+=(const string& _Str)
{
	Append(_Str);
	return (*this);
}

void my_std::string::resize(size_type _Size)
{
	_Realloc(_Size);
	mSize = _Size;
}

void my_std::string::reserve(size_type _Size)
{
	_Realloc(_Size);
}

my_std::string::reference my_std::string::at(size_type _Idx)
{
	if (mSize < _Idx)
	{
		throw std::out_of_range("try to access over size");
	}
	return mPtr[_Idx];
}

my_std::string::reference my_std::string::back()
{
	if (true == empty())
	{
		throw std::out_of_range("back() called empty string");
	}
	return mPtr[mSize - 1];
}

my_std::string::reference my_std::string::front()
{
	if (true == empty())
	{
		throw std::out_of_range("back() called empty string");
	}
	return mPtr[0];
}

void my_std::string::Append(const_pointer _Str)
{
	const size_type Len = strlen(_Str);
	_Realloc(mSize + Len);

	for (size_t i = 0; i < Len + 1; i++)
	{
		mPtr[mSize + i] = _Str[i];
	}

	mSize += Len;
}

void my_std::string::Append(string _Str)
{
	Append(_Str.c_str());
}

my_std::string my_std::string::substr(size_type _Off /*= 0*/, size_type _Count /*= -1*/) const
{
	string Result;

	if ((_Off < 0) || (mSize < _Off + _Count))
	{
		throw std::out_of_range("The specified range has benn exceeded.");
	}

	Result._Realloc(_Count);

	const size_type	CopyRange = _Off + _Count;

	for (size_t i = _Off; i < CopyRange; i++)
	{
		Result.mPtr[i] = mPtr[i];
	}

	Result.mSize = _Count;

	return Result;
}

void my_std::string::_Realloc(size_type _Size)
{
	const size_type Ratio = 2;
	if (mCapacity * Ratio < _Size)
	{
		_Alloc(_Size);
	}
	else if (mCapacity < _Size)
	{
		_Alloc(mCapacity * Ratio);
	}
}

void my_std::string::_Alloc(size_type _Size)
{
	if (nullptr != mPtr)
	{
		_Destroy();
	}

	mPtr = new value_type[_Size + 1];
	mCapacity = _Size;
}

void my_std::string::_Destroy()
{
	if (nullptr == mPtr)
	{
		return;
	}

	delete[] mPtr;
	mPtr = nullptr;

	mSize = 0;
	mCapacity = 0;
}

my_std::string my_std::operator+(const string& _lhs, const string& _rhs)
{
	string Result = _lhs;
	Result.Append(_rhs);
	return Result;
}

