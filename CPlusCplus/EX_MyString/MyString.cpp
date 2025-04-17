#include "MyString.h"

#include <cstring>
#include <assert.h>

#define CSTR_LEN(x) static_cast<int>(std::strlen(x))
#define INT_MIN(a,b) a < b ? a : b;


int MyString::Compare(const MyString& lhs, const MyString& rhs)
{
	const int MIN = INT_MIN(lhs.mlength, rhs.mlength);
	for (int i = 0; i < MIN; i++)
	{
		if (lhs.mStr[i] < rhs.mStr[i])
		{
			return 1;
		}
		else if (lhs.mStr[i] > rhs.mStr[i])
		{
			return -1;
		}
	}

	if (lhs.mlength < rhs.mlength)
	{
		return 1;
	}
	else if (lhs.mlength > rhs.mlength)
	{
		return -1;
	}

	return 0;
}

int MyString::Compare(const char* lhs, const char* rhs)
{
	const int L_Length = CSTR_LEN(lhs);
	const int R_Length = CSTR_LEN(rhs);
	if (L_Length < R_Length)
	{
		return 1;
	}
	else if (L_Length > R_Length)
	{
		return -1;
	}

	for (int i = 0; i < L_Length; i++)
	{
		if (lhs[i] < rhs[i])
		{
			return 1;
		}
		else if (lhs[i] > rhs[i])
		{
			return -1;
		}
	}

	return 0;
}

MyString::MyString(int _capacity)
{
	assert(0 < _capacity);
	Reserve(_capacity);
}

MyString::MyString(char c, int n)
{
	Reserve(n);
	for (int i = 0; i < n; i++)
	{
		mStr[i] = c;
	}

	mStr[n] = '\0';
	mlength = n;
}

MyString::MyString(const char* s)
{
	add_string(s);
}

MyString::MyString(const MyString& s)
{
	add_string(s);
}

MyString::~MyString()
{
	Destroy();
}

MyString MyString::operator+(const MyString& Str) const
{
	MyString Result = MyString(*this);
	Result.add_string(Str);
	return Result;
}

MyString& MyString::operator+=(const MyString& Str)
{
	return add_string(Str);
}

bool MyString::operator==(const MyString& Str)
{
	return !Compare(*this, Str);
}

bool MyString::operator!=(const MyString& Str)
{
	return !(*this == Str);
}

bool MyString::operator<(const MyString& Str)
{
	return (1 == Compare(*this, Str));
}

bool MyString::operator<=(const MyString& Str)
{
	return (*this == Str) || (*this < Str);
}

MyString& MyString::add_string(const char* _str)
{
	const int Len = CSTR_LEN(_str);

	const int BufferSize = mlength + Len;

	Reserve(BufferSize);
	copy_string(mlength, _str, Len);
	mStr[mlength + Len] = '\0';
	mlength = BufferSize;

	return *this;
}

MyString& MyString::add_string(const MyString& s)
{
	add_string(s.mStr);
	return *this;
}

void MyString::copy_string(const char* _str)
{
	const int LEN = CSTR_LEN(mStr);
	copy_string(0, _str, LEN);
}

void MyString::copy_string(const MyString& s)
{
	copy_string(0, s);
}

void MyString::copy_string(int Pos, const MyString& s)
{
	copy_string(Pos, s.mStr, s.mlength);
}

void MyString::copy_string(int Pos, const char* _str)
{
	const int LEN = CSTR_LEN(_str);
	copy_string(Pos, _str, LEN);
}

void MyString::copy_string(int Pos, const char* _str, int n)
{
	// buffer가 충분히 할당되어 있지 않습니다.
	assert(Pos + n <= mcapacity);

	for (int i = 0; i < n; i++)
	{
		mStr[Pos + i] = _str[i];
	}
}

void MyString::Insert(int Pos, const char* _Str)
{
	if (Pos < 0 || mlength < Pos)
	{
		return;
	}

	const int LENGTH = CSTR_LEN(_Str);
	const int CopySize = LENGTH + mlength;
	if (mcapacity < CopySize)
	{
		Reserve(CopySize);
	}

	// 삽입할 위치 이후의 문자열을 뒤로 미룬다.
	for (int i = mlength - 1; Pos <= i; --i)
	{
		mStr[i + LENGTH] = mStr[i];
	}

	// 삽입할 문자열 복사
	copy_string(Pos, _Str);

	mStr[CopySize] = '\0';
	mlength = CopySize;
}

void MyString::Insert(int Pos, const MyString& _Str)
{
	Insert(Pos, _Str.mStr);
}

void MyString::Erase(int Pos, int Num)
{
	if (Pos < 0 
		|| Num < 0
		|| mlength < Pos)
	{
		return;
	}

	for (int i = 0; i < mlength - Num; i++)
	{
		mStr[Pos + i] = mStr[Pos + Num + i];
	}

	mStr[mlength - Num] = '\0';
	mlength -= Num;
}

int MyString::Find(int From, const char* _Str) const
{
	const int LENGTH = CSTR_LEN(_Str);
	for (int Pos = From; Pos < mlength - LENGTH; Pos++)
	{
		for (int i = 0; i < LENGTH; i++)
		{
			if (mStr[i + Pos] != _Str[i])
			{
				break;
			}

			if (LENGTH == i + 1)
			{
				return Pos;
			}
		}
	}

	return -1;
}

int MyString::Find(int From, const MyString& s) const
{
	return Find(From, s.mStr);
}

char& MyString::at(int Pos)
{
	assert(Pos <= mlength);
	return mStr[Pos];
}

inline const char& MyString::at(int Pos) const
{
	assert(Pos <= mlength);
	return mStr[Pos];
}

void MyString::Reserve(int _size)
{
	if (mcapacity < _size)
	{
		// 빈번한 메모리 할당/해제 비용을 줄이기 위해 넉넉한 크기를 할당한다.
		const int BufferSize = (mcapacity * 2 <= _size ? _size : mcapacity * 2) + 1;

		char* CopyBuffer = new char[mlength];
		for (int i = 0; i < mlength; i++)
		{
			CopyBuffer[i] = mStr[i];
		}

		Destroy();
		mStr = new char[BufferSize];
		mcapacity = BufferSize - 1;

		copy_string(0, CopyBuffer, mlength);

		if (nullptr != CopyBuffer)
		{
			delete[] CopyBuffer;
			CopyBuffer = nullptr;
		}
	}
}

void MyString::Destroy()
{
	if (nullptr != mStr)
	{
		delete[] mStr;
		mStr = nullptr;
	}
}

MyString operator+(const char* _StrA, const MyString& _StrB)
{
	return MyString(_StrA).operator+(_StrB);
}
