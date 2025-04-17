#pragma once

#ifndef __DEFINE_ARRAY_H
#define __DEFINE_ARRAY_H
#include <cassert>
#include <memory>

template <typename T>
class TArray
{
	using data_type = T;
	using size_type = int;

public:
	TArray()
	{

	}
	TArray(int _Size)
	{
		mPtr = new data_type[_Size];
		mSize = _Size;
	}
	~TArray()
	{
		Destroy();
	}

	// delete function
	TArray(const TArray& _Other)
	{
		Alloc(_Other.size());
		Copy(_Other);
	}

	TArray& operator=(const TArray& _Other)
	{
		Destroy();
		Alloc(_Other.size());
		Copy(_Other);

		return *this;
	}

	inline data_type& operator[](int _Index)
	{
		return at(_Index);
	}

	data_type& at(int _Index)
	{
		assert(_Index < mSize);
		return mPtr[_Index];
	}
	const data_type& at(int _Index) const
	{
		assert(_Index < mSize);
		return mPtr[_Index];
	}

	inline size_type size() const { return mSize; }

	void Resize(int _Size)
	{
		ReAlloc(_Size);
	}

private:
	void ReAlloc(int _Size)
	{
		if (_Size < mSize)
		{
			return;
		}

		data_type* Buffer = nullptr;
		if (0 != mSize)
		{
			Buffer = new data_type[mSize];
			memcpy_s(Buffer, mSize, mPtr, mSize);

			Destroy();
		}

		Alloc(_Size);

		if (nullptr != Buffer)
		{
			memcpy_s(mPtr, mSize, Buffer, mSize);

			for (int i = mSize; i < _Size; i++)
			{
				mPtr[i] = 0;
			}

			delete[] Buffer;
			Buffer = nullptr;
		}
		else
		{
			for (int i = 0; i < _Size; i++)
			{
				mPtr[i] = 0;
			}
		}
	}

	void Alloc(int _Size)
	{
		assert(nullptr == mPtr);
		mPtr = new data_type[_Size];
		mSize = _Size;
	}

	void Copy(const TArray& _Other)
	{
		assert(mSize == _Other.mSize);
		memcpy_s(mPtr, _Other.mSize, _Other.mPtr, _Other.mSize);
	}

	void Destroy()
	{
		if (nullptr != mPtr)
		{
			delete[] mPtr;
			mPtr = nullptr;
		}

		mSize = 0;
	}

private:
	data_type* mPtr = nullptr;
	size_type mSize = 0;

};



#endif // !__DEFINE_ARRAY_H


