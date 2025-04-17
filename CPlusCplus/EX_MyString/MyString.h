#pragma once

#ifndef __DEFINE_MY_STRING_
#define __DEFINE_MY_STRING_

#include <iostream>

class MyString 
{
private:
	char* mStr = nullptr;
	int mlength = 0;
	int mcapacity = 0;

public:
	friend std::ostream& operator<<(std::ostream& os, const MyString& Str);

	static int Compare(const MyString& lhs, const MyString& rhs);
	static int Compare(const char* lhs, const char* rhs);

public:
	// 전달받을 인자에 대해 자신의 타입을 받을 수 있도록 명시적으로 선언되어 있습니다.
	// 해당 함수는 전달받을 인자만큼 버퍼를 할당합니다.
	explicit MyString(int _capacity);
	MyString(char c, int n);  // 문자 c 가 n 개 있는 문자열로 정의
	MyString(const char* s);
	MyString(const MyString& s);
	~MyString();

	inline char& operator[](int _Idx)
	{
		return at(_Idx);
	}

	MyString operator+(const MyString& Str) const;
	MyString& operator+=(const MyString& Str);

	bool operator==(const MyString& Str);
	bool operator!=(const MyString& Str);
	bool operator<(const MyString& Str);
	bool operator<=(const MyString& Str);

	MyString& add_string(const char* str);
	MyString& add_string(const MyString& s);   // str 뒤에 s 를 붙인다.
	void copy_string(const MyString& s);  // str 에 s 를 복사한다.
	void copy_string(const char* str);
	void copy_string(int Pos, const MyString& s);  // str 에 s 를 복사한다.
	void copy_string(int Pos, const char* _str);
	void copy_string(int Pos, const char* str, int n);
	void Insert(int Pos, const char* _Str);
	void Insert(int Pos, const MyString& _Str);
	void Erase(int Pos, int Num);
	int Find(int From, const char* _Str) const;
	int Find(int From, const MyString& s) const;
	int size() const { return mlength; }
	const char* const Get() const { return mStr; }
	char& at(int Pos);
	const char& at(int Pos) const;
	int capacity() const { return mcapacity; }

private:
	void Reserve(int _size);
	void Destroy();
};

inline std::ostream& operator<<(std::ostream& os, const MyString& _Str)
{
	os << _Str.mStr;
	return os;
}

MyString operator+(const char* _StrA, const MyString& _StrB);

#endif // !__DEFINE_MY_STRING_