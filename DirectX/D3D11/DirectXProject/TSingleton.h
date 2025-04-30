#pragma once
#include <type_traits>
#include <memory>
#include <cstdlib>

#include "Header.h"

template<typename ObjectType>
class TSingleton
{
	// static member function
public:
	static ObjectType* GetInstance()
	{
		if (false == std::is_base_of<TSingleton<ObjectType>, ObjectType>::value)
		{
			MessageBoxAssert(L"It is not an inheritance hierarchy.");
			return nullptr;
		}

		if (nullptr == s_Instance)
		{
			s_Instance = new ObjectType;
			atexit(TSingleton::DestroyInstance);
		}

		return static_cast<ObjectType*>(s_Instance);
	}

	static void DestroyInstance()
	{
		safe_delete(s_Instance);
	}

	// static member variable
private:
	static TSingleton<ObjectType>* s_Instance;

	// non-static member
public:
	// destructor
	virtual ~TSingleton() {}

	// delete function
	TSingleton(const TSingleton& _Other) = delete;
	TSingleton& operator=(const TSingleton& _Other) = delete;

protected:
	// constructor 
	TSingleton() {}

};

template <typename ObjectType>
inline TSingleton<ObjectType>* TSingleton<ObjectType>::s_Instance = nullptr;
