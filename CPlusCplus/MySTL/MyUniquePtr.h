#pragma once

#ifndef __DEFINE_MYUNIQUEPTR_H
#define __DEFINE_MYUNIQUEPTR_H

#include "Header.h"

// 객체가 알아서 자원을 관리하도록 한다.
template<typename T>
class MyUniquePtr final
{
public:
	MyUniquePtr() = default;
	~MyUniquePtr()
	{
		safe_delete(mPtr);
	}

	MyUniquePtr(T* _Object)
		: mPtr(_Object)
	{

	}

	MyUniquePtr(const MyUniquePtr& _Other) = delete;
	MyUniquePtr(MyUniquePtr&& _Other) noexcept
	{
		mPtr = _Other.mPtr;
		_Other.mPtr = nullptr;
	}

	MyUniquePtr& operator=(const MyUniquePtr& _Other) = delete;
	MyUniquePtr& operator=(MyUniquePtr&& _Other) noexcept
	{
		mPtr = _Other.mPtr;
		_Other.mPtr = nullptr;
		return *this;
	}

	T* Get() { return mPtr; }
	const T* Get() const { return mPtr; }

	void release()
	{
		safe_delete(mPtr);
	}

private:
	T* mPtr = nullptr;

};

// 인자는 &&로 전달하는데, 겹침 규칙으로 타입 형태가 유지됨
template<typename ObjectType, typename... Types>
MyUniquePtr<ObjectType> make_my_unique_ptr(Types&&... _Args)
{
	ObjectType* NewObject = new ObjectType(std::forward<Types>(_Args)...);
	MyUniquePtr<ObjectType> Unique = MyUniquePtr<ObjectType>(NewObject);
	return std::move(Unique);

	// 한줄로 축약 가능
	return MyUniquePtr<ObjectType>(new ObjectType(std::forward<Types>(_Args)...));
}

#endif // !__DEFINE_MYUNIQUEPTR_H
