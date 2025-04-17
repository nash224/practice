#pragma once

#ifndef __DEFINE_MYVECTOR_H
#define __DEFINE_MYVECTOR_H

#include <cassert>
#include <memory>
#include "Header.h"

template<typename T> class MyVector;

template<typename T>
class iterator_base
{
	friend class MyVector<T>;

public:
	iterator_base(T* _Data = nullptr)
		: mPtr(_Data)
	{
	}

	iterator_base& operator++()
	{
		++mPtr;
		return (*this);
	}

	iterator_base operator++(int)
	{
		iterator_base Temp = iterator_base(*this);
		++mPtr;
		return Temp;
	}

	bool operator==(const iterator_base& _Other) const
	{
		return (mPtr == _Other.mPtr);
	}

	bool operator!=(const iterator_base& _Other) const
	{
		return !operator==(_Other);
	}

	T& operator*() 
	{
		assert(nullptr != mPtr);
		return *mPtr;
	}

protected:
	T* mPtr = nullptr;
};

template<typename T>
class const_iterator_base 
{
	friend class MyVector<T>;

public:
	const_iterator_base(T* _Data = nullptr)
		: mPtr(_Data)
	{
	}

	const_iterator_base& operator++()
	{
		++mPtr;
		return (*this);
	}

	const_iterator_base operator++(int)
	{
		const_iterator_base Temp = const_iterator_base(*this);
		++mPtr;
		return Temp;
	}
	

	bool operator==(const const_iterator_base<T>& _Other) const
	{
		return (mPtr == _Other.mPtr);
	}

	bool operator!=(const const_iterator_base<T>& _Other) const
	{
		return !operator==(_Other);
	}

	const T& operator*() const
	{
		assert(nullptr != mPtr);
		return *mPtr;
	}

protected:
	T* mPtr = nullptr;

};

template <typename T>
class MyVector
{
public:
	static constexpr int NOTFOUND = -1;

public:
	using data_type = T;
	using size_type = int;
	using capacity_type = size_type;
	using pos_type = int;
	using iterator = iterator_base<T>;
	using const_iterator = const_iterator_base<T>;

public:
	MyVector() = default;

	MyVector(capacity_type _Capa)
	{
		resize(_Capa);
	}

	~MyVector()
	{
		Destroy();
	}

	MyVector(const MyVector& _Other)
	{
		Alloc(_Other.capacity());
		Copy(_Other.mPtr, _Other.size());
		mLength = _Other.size();
	}
	MyVector(MyVector&& _Other) noexcept
	{
		mPtr = _Other.mPtr;
		_Other.mPtr = nullptr;
		mCapacity = _Other.mCapacity;
		mLength = _Other.mLength;
		_Other.mCapacity = 0;
		_Other.mLength = 0;
	}

	MyVector& operator=(const MyVector& _Other)
	{
		Destroy();
		Alloc(_Other.capacity());
		Copy(_Other.mPtr, _Other.size());
		mLength = _Other.size();
	}

	MyVector& operator=(MyVector&& _Other) noexcept
	{
		mPtr = _Other.mPtr;
		_Other.mPtr = nullptr;
		mCapacity = _Other.mCapacity;
		mLength = _Other.mLength;
		_Other.mCapacity = 0;
		_Other.mLength = 0;
	}

	T& operator[](int _Index)
	{
		return mPtr[_Index];
	}

	void reserve(size_type _Size)
	{
		Realloc(_Size);
	}

	void resize(size_type _Size)
	{
		Realloc(_Size);
		mLength = _Size;
	}

	void push_back(const T& _Data)
	{
		Realloc(mLength + 1);
		mPtr[mLength] = _Data;
		++mLength;
	}

	void pop_back()
	{
		if (mLength <= 0)
		{
			return;
		}

		--mLength;
	}

	void insert(const iterator& _Where, const T& _Data)
	{
		int Pos = Find(_Where);

		assert(0 <= Pos && Pos <= mLength);

		Realloc(mLength + 1);

		const bool bEnd = (Pos == mLength);
		if (!bEnd)
		{
			for (int i = mLength; Pos <= i; --i)
			{
				mPtr[i + 1] = mPtr[i];
			}
		}

		mPtr[Pos] = _Data;

		++mLength;
	}

	iterator erase(const iterator& _Where)
	{
		assert(nullptr != _Where.mPtr);
		pos_type Pos = Find(_Where);
		assert(mLength != Pos);

		const bool bEnd = (Pos == mLength);
		if (!bEnd)
		{
			for (size_type i = Pos; i < mLength - 1; i++)
			{
				mPtr[i] = mPtr[i + 1];
			}
		}

		--mLength;

		return iterator(&mPtr[Pos]);
	}

	void clear()
	{
		mLength = 0;
	}

	T& at(int _Index)
	{
		assert(_Index < mLength);
		return mPtr[_Index];
	}

	T& back()
	{
		assert(!empty());
		return mPtr[mLength - 1];
	}

	inline const T& at(int _Index) const { return at(_Index); }
	inline size_type size() const { return mLength; };
	inline capacity_type capacity() const { return mCapacity; };
	inline bool empty() const { return (0 == mLength); }

	// iterator
public:
	iterator begin()
	{
		return iterator(&mPtr[0]);
	}

	const iterator begin() const { return &mPtr[0]; }

	iterator end() const { return iterator(&mPtr[mLength]); }

	const_iterator cbegin()
	{
		T* pData = empty() ? nullptr : &mPtr[0];
		return const_iterator(pData);
	}

	const_iterator cend() const { return const_iterator(&mPtr[mLength]); }

private:
	// TODO : 삭제가 예정된 함수입니다.
	int Find(const iterator& _Where) const
	{
		int Pos = NOTFOUND;
		iterator StartIter = begin();
		for (Pos = 0; StartIter != _Where; ++Pos, ++StartIter) {}

		return Pos;
	}

	void Realloc(size_type _Size)
	{
		if (_Size <= mCapacity)
		{
			return;
		}

		const int AllocSize = mCapacity * 2 < _Size ? _Size : mCapacity * 2;

		if (nullptr != mPtr)
		{
			T* Temp = new T[mLength];
			CopyMemory(Temp, mLength, mPtr, mLength);
			Destroy();
			Alloc(AllocSize);
			Copy(Temp, mLength);

			safe_array_delete(Temp);
		}
		else
		{
			Alloc(AllocSize);
		}
	}

	void Alloc(capacity_type _Size)
	{
		assert(nullptr == mPtr);
		mPtr = new T[_Size];
		std::uninitialized_fill_n(mPtr, _Size, T());
		mCapacity = _Size;
	}

	void Destroy()
	{
		safe_array_delete(mPtr);
		mCapacity = 0;
	}

	void Copy(T* _Src, size_type _SrcSize)
	{
		assert(_SrcSize <= mCapacity);
		CopyMemory(mPtr, mCapacity, _Src, _SrcSize);
	}

	static void CopyMemory(T* _Dest, size_type _DestSize, T* _Src, size_type _SrcSize)
	{
		memcpy_s(_Dest, sizeof(T) * _DestSize, _Src, sizeof(T) * _SrcSize);
	}

private:
	T* mPtr = nullptr;
	size_type mLength = 0;
	capacity_type mCapacity = 0;

};

#endif // !__DEFINE_MYVECTOR_H


