#pragma once

#ifndef __DEFINE_MYARRAY_H
#define __DEFINE_MYARRAY_H

#include <cassert>

template <typename T, int N>
class MyArray
{
private:
	using size_type = int;

public:
	MyArray() = default;
	MyArray(T (&_Arr)[N])
	{
		assert(0 < N);
		const int LENGTH = static_cast<int>(N);
		for (int i = 0; i < LENGTH; i++)
		{
			mArr[i] = _Arr[i];
		}
	}

	T& operator[](int _Index) { return mArr[_Index]; }

	size_type size() const { return N; }
	T& front() { return mArr[0]; };
	T& back() { return mArr[N - 1]; };
	const T& at(unsigned int _Index) const { return at(_Index); }
	T& at(unsigned int _Index) 
	{ 
		assert(_Index < N);
		return mArr[_Index];
	};

	bool empty() const { return false; };

	void fill(const T& _Value)
	{
		for (size_type i = 0; i < N; i++)
		{
			mArr[i] = _Value;
		}
	}


private:
	T mArr[N];

};

#endif // !__DEFINE_MYARRAY_H


