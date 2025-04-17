// MySTL.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stack>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <memory>
#include <thread>
#include<mutex>
#include <crtdbg.h>

#include "MyStack.h"
#include "MyVector.h"
#include "MyArray.h"
#include "MyList.h"
#include "MySet.h"
#include "MyUniquePtr.h"
#include "MyMutex.h"

template<typename T>
void PrintType(const T& _TArg)
{
	std::cout << "typeid: " << typeid(_TArg).name() << '\n';
}

// TODO : MyVector<T>::const_iterator가 작동하지 않는 문제가 있음
template<typename T>
void PrintContainer(T& _TVec)
{
	std::cout << "Ranged for (Vector): "<< "\n";
	for (auto& i : _TVec)
	{
		std::cout << i << ' ';
	}

	std::cout << "\n";
}

class Int
{
public:
	Int(int _Data = 0) : Data(_Data) {}
	// bool operator<(const Int& _Other) const { return Data <_Other.Data; }
	operator int() const { return Data; }

	int Data;
};

struct IntCompare
{
	bool operator()(const Int& _lhs, const Int& _rhs) const { return _lhs.Data < _rhs.Data; }
};


void Counter(MyMutex& _m, int* _pCount);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	static_assert(sizeof(void *) != 4, "Can't build 32bit os");

	// mutex
	if (true)
	{
		MyMutex Lock;

		const int NUM_OF_WORKER = 5;
		std::vector<std::thread> Workers;

		int Count = 0;

		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(Counter, std::ref(Lock), &Count));
		}

		for (std::thread& i : Workers)
		{
			i.join();
		}

		std::cout << "Result: " << Count << '\n';
	}

	if (false)
	{
		if (true)
		{
			std::unique_ptr<Int> Object = std::make_unique<Int>(55);
#if 0
			std::unique_ptr<Int> ObjectB = Object;
#endif // 0

			std::unique_ptr<Int> ObjectB = std::move(Object);
			Int* Ptr = ObjectB.get();
			std::cout << Ptr->Data << '\n';
		}

		if (true)
		{
			MyUniquePtr<Int> Object = make_my_unique_ptr<Int>(55);
#if 0
			std::unique_ptr<Int> ObjectB = Object;
#endif // 0

			MyUniquePtr<Int> ObjectB = std::move(Object);
			Int* Ptr = ObjectB.Get();
			std::cout << Ptr->Data << '\n';
		}
	}

	// set
	if (false)
	{
		if (true)
		{
			typedef std::set<Int>::iterator SetIter;
			std::set<Int, IntCompare> st;
			st.insert(5);
			st.insert(2);
			st.insert(5);
			st.insert(7);
			st.insert(5);
			st.insert(5);
			st.erase(5);

			if (st.end() != st.find(3))
			{
				int a = 0;
			}

			if (st.end() != st.find(5))
			{
				int a = 0;
			}

			st.erase(7);
			st.clear();
		}


	}

	if (false)
	{
		if (false)
		{
			std::stack<int> St;
			St.push(5);
			St.pop();
			bool IsEmpty = St.empty();
		}

		if (true)
		{
			int TOP = 0;
			MyStack<int> MySt;
			MySt.Push(5);
			MySt.Push(4);
			MySt.Push(3);
			TOP = MySt.Top();
			MySt.Pop();
			TOP = MySt.Top();
			MySt.clear();
		}
	}

	// vector trace
	if (false)
	{
		if (true)
		{
			std::vector<int> Vec(5);
			Vec.push_back(5);
			Vec.push_back(3);
			Vec.push_back(2);

			std::vector<int> OtherVec = Vec;

			const size_t Size = Vec.size();
			const size_t Capa = Vec.capacity();
			int Back = Vec.back();
			Back = Vec.at(2);
			Back = Vec[2];

			Vec.reserve(5);
			Vec.resize(5);
			Vec.pop_back();
			Vec.clear();
			const bool IsEmpty = Vec.empty();

			std::vector<int> VecB;
			auto FirstIter = VecB.begin();
			VecB.push_back(3);
			VecB.push_back(2);
			VecB.push_back(1);
			VecB.insert(VecB.end(), 4);
			VecB.insert(VecB.begin(), 5);
			VecB.erase(VecB.begin());

			std::vector<int>::iterator StartIter = VecB.begin();
			std::vector<int>::iterator EndIter   = VecB.end();

			for (;StartIter != EndIter; ++StartIter)
			{
				std::cout << (*StartIter);
			}

			std::cout << '\n';

			if (false)
			{
				auto Value = (*StartIter);
			}

			std::vector<int>::const_iterator cStartIter = VecB.cbegin();
			std::vector<int>::const_iterator cEndIter   = VecB.cend();

			PrintType(VecB.cbegin());
			PrintContainer(VecB);
		}

		if (true)
		{
			MyVector<int> Vec(5);
			Vec.push_back(5);
			Vec.push_back(3);
			Vec.push_back(2);

			MyVector<int> OtherVec = Vec;

			const size_t Size = Vec.size();
			const size_t Capa = Vec.capacity();
			int Back = Vec.back();
			Back = Vec.at(2);
			Back = Vec[2];

			Vec.reserve(5);
			Vec.resize(5);
			Vec.pop_back();
			Vec.clear();
			const bool IsEmpty = Vec.empty();

			MyVector<int> VecB;
			auto FirstIter = VecB.begin();
			VecB.push_back(3);
			VecB.push_back(2);
			VecB.push_back(1);
			VecB.insert(VecB.end(), 4);
			VecB.insert(VecB.begin(), 5);
			VecB.erase(VecB.begin());
			// VecB.erase(VecB.end());

			MyVector<int>::iterator StartIter = VecB.begin();
			MyVector<int>::iterator EndIter = VecB.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				const int Data = (*StartIter);
				std::cout << (*StartIter);
			}

			std::cout << '\n';

			if (false)
			{
				auto Value = (*StartIter);
			}

			MyVector<int>::const_iterator cStartIter = VecB.cbegin();
			MyVector<int>::const_iterator cEndIter = VecB.cend();

			PrintType(VecB.cbegin());
			PrintContainer(VecB);
		}
	}

	// array trace
	if (false)
	{
		if (true)
		{
			std::array<int, 10> Arr = {0,1,2,3,4,5,6,7,8,9};
			const int SIZE = static_cast<int>(Arr.size());
			const int NUM = Arr.at(2);
			const int NUMA = Arr[2];
			const int BACK = Arr.back();
			const int FRONT = Arr.front();
			const bool bEmpty = Arr.empty();
			Arr.fill(5);

			int a = 0;
		}

		if (true)
		{
			const int ARR_SIZE = 10;
			int ArrSrc[ARR_SIZE] = { 0,1,2,3,4,5,6,7,8,9 };
			MyArray<int, ARR_SIZE> Arr = ArrSrc;
			const int SIZE = static_cast<int>(Arr.size());
			const int NUM = Arr.at(2);
			const int NUMA = Arr[2];
			const int BACK = Arr.back();
			const int FRONT = Arr.front();
			const bool bEmpty = Arr.empty();
			Arr.fill(5);

			int a = 0;
		}

		std::cout << "(typeid(MyArray<int, 5>) == (typeid(MyArray<int, 4>))) is type same? : " << (typeid(MyArray<int, 5>) == (typeid(MyArray<int, 4>))) << '\n';
	}

	// List trace
	if (false)
	{
		if (true)
		{
			std::list<int> List;
			List.push_back(1);
			List.push_back(2);
			List.push_back(3);
			List.push_back(3);
			List.push_back(3);
			List.push_back(4);
			List.push_front(0);
			List.pop_back();
			List.pop_front();
			const auto BackValue = List.back();
			const auto FrontValue = List.front();

			//iterator
			List.erase(List.begin());
			List.remove(3);

			std::list<int>::iterator StartIter = List.begin();
			std::list<int>::iterator EndIter = List.end();
			for (;StartIter != EndIter; ++StartIter)
			{
				std::cout << (*StartIter);
			}

			std::cout << '\n';

			List.insert(List.begin(), 5);

			// List.clear();
			const bool bEmpty = List.empty();

			PrintContainer(List);
			PrintType(List);

			int a = 0;
		}

		if (true)
		{
			MyList<int> List;
			List.push_back(1);
			List.push_back(2);
			List.push_back(3);
			List.push_back(3);
			List.push_back(3);
			List.push_back(4);
			List.push_front(0);
			List.pop_back();
			List.pop_front();
			const auto BackValue = List.back();
			const auto FrontValue = List.front();

			//iterator
			List.erase(List.begin());
			List.remove(3);

			MyList<int>::iterator StartIter = List.begin();
			MyList<int>::iterator EndIter = List.end();
			for (; StartIter != EndIter; ++StartIter)
			{
				std::cout << (*StartIter) << ' ';
			}

			std::cout << '\n';

			List.insert(List.begin(), 5);

			// List.clear();
			const bool bEmpty = List.empty();

			PrintType(List);

			int a = 0;
		}
	}

	// Degue
	if (false)
	{
		if (true)
		{
			std::deque<int> dp(5);
			dp.push_back(5);
			dp.push_back(3);
			dp.push_back(2);

			std::deque<int> OtherVec = dp;

			const size_t Size = dp.size();
			int Back = dp.back();
			Back = dp.at(2);
			Back = dp[2];

			dp.resize(5);
			dp.pop_back();
			dp.clear();
			const bool IsEmpty = dp.empty();

			std::deque<int> dpB;
			auto FirstIter = dpB.begin();
			dpB.push_back(3);
			dpB.push_back(2);
			dpB.push_back(1);
			dpB.insert(dpB.end(), 4);
			dpB.insert(dpB.begin(), 5);
			dpB.erase(dpB.begin());

			std::deque<int>::iterator StartIter = dpB.begin();
			std::deque<int>::iterator EndIter = dpB.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				std::cout << (*StartIter);
			}

			std::cout << '\n';

			if (false)
			{
				auto Value = (*StartIter);
			}

			std::deque<int>::const_iterator cStartIter = dpB.cbegin();
			std::deque<int>::const_iterator cEndIter = dpB.cend();

			PrintType(dpB.cbegin());
			PrintContainer(dpB);
		}
	}

    std::cout << "Hello World!\n";
}

std::atomic<bool> Key;
bool IsLock = false;
void lock()
{
	while (false == Key.compare_exchange_strong(IsLock, true))
	{
	}
}

void unlock();

void Counter(MyMutex& _m, int* _pCount)
{
	assert(_pCount);
	for (int i = 0; i < 10000; i++)
	{
		_m.lock();
		++(*_pCount);
		_m.unlock();
	}
}

void unlock()
{
	Key.compare_exchange_strong(IsLock, false);
}