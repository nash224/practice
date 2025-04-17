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
	// ���޹��� ���ڿ� ���� �ڽ��� Ÿ���� ���� �� �ֵ��� ��������� ����Ǿ� �ֽ��ϴ�.
	// �ش� �Լ��� ���޹��� ���ڸ�ŭ ���۸� �Ҵ��մϴ�.
	explicit MyString(int _capacity);
	MyString(char c, int n);  // ���� c �� n �� �ִ� ���ڿ��� ����
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
	MyString& add_string(const MyString& s);   // str �ڿ� s �� ���δ�.
	void copy_string(const MyString& s);  // str �� s �� �����Ѵ�.
	void copy_string(const char* str);
	void copy_string(int Pos, const MyString& s);  // str �� s �� �����Ѵ�.
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