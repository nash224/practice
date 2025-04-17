// 21_SmartPointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <crtdbg.h>
#include <memory>

// 컴퓨터 공학에서 자원이란, 운영체제가 사용자에게 빌려준 모든 것이다.
// 예를들어, 힙 메모리, 파일 핸들 등이 있다.

// 이러한 자원은 c++에서 운영체제가 사용자에게 빌려주면, 사용자는 의무적으로 반환해야한다.
// 반환하지 않을 경우, 프로그램이 종료되기 전까지 절때 지워지지 않음

class BigMemory
{
public:
	BigMemory(int _Size)
	{
		std::cout << "자원 획득!\n";
		mPtr = new int[_Size];
		mSize = _Size;
	}

	~BigMemory()
	{
		std::cout << "자원 반환!\n";
		if (nullptr != mPtr)
		{
			delete[] mPtr;
			mPtr = nullptr;
		}
	}

	BigMemory(const BigMemory& _Other)
	{
		mPtr = new int[_Other.mSize];
		mSize = _Other.mSize;
	}

	void DoSomething() 
	{
		if (nullptr == mPtr)
		{
			return;
		}

		int a = 5;
		int b = 5;
		mPtr[5] = a + b;
	}

	void SetOther(std::shared_ptr<BigMemory> _Owner)
	{
		mOther = _Owner;
	}

	void SetWeakOther(const std::shared_ptr<BigMemory>& _Owner)
	{
		mwOther = _Owner;
	}

	int GetOtherSize() const
	{
		// shared_ptr이 가리키는 객체는 소멸되었는가?
		if (true == mwOther.expired())
		{
			return -1;
		}

		// weak_ptr로 객체를 참조하려면 shared_ptr로 변환해서 사용해야 함
		// const shared<T>& 는 값 변경도 하지 않고 레퍼런스 카운터도 증가시키지 않겠다는 의미
		const std::shared_ptr<BigMemory>& Ref = mwOther.lock();
		return Ref->mSize;
	}

private:
	int* mPtr = nullptr;
	int mSize = 0;
	std::shared_ptr<BigMemory> mOther;
	std::weak_ptr<BigMemory> mwOther;
};

// 무언가를 수행합니다.
void foo()
{
	// 자원은 획득했으나 반환을 하지 않은 경우
	BigMemory* Ptr = new BigMemory(500);
	Ptr->DoSomething();

	// {162} normal block at 0x000001B9C96777F0, 2000 bytes long.
	// 어우... 심장떨려... 4btye만 누수나도 떨리는데 2000은..
}

// 무언가를 수행합니다.
void bar()
{
	// 자원은 획득했으나 예기치 못한 상황으로 메모리를 반환을 하지 않은 경우
	BigMemory* Ptr = new BigMemory(500);
	Ptr->DoSomething();

	// 의도적으로 throw를 던짐
	throw 1;

	// throw 아래의 식은 실행되지 않음
	delete Ptr;

	// {162} normal block at 0x000001B9C96777F0, 2000 bytes long.
	// 어우... 심장떨려... 4btye만 누수나도 떨리는데 2000은..
}

// unique_ptr을 인자로 전달받아 무언가를 수행합니다.
void UniqueDoSomething(BigMemory* _Ptr)
{
	if (nullptr == _Ptr)
	{
		throw 2;
	}

	_Ptr->DoSomething();
}
// unique_ptr을 인자로 전달받아 무언가를 수행합니다.
void UniqueDoSomething(std::unique_ptr<BigMemory>& _Ptr)
{
	if (nullptr == _Ptr.get())
	{
		return;
	}

	_Ptr->DoSomething();
}

void Unique()
{
	// 스택 객체에 내 자원을 관리하도록 한다.
	// unique_ptr은 부여한 자원에 대해 유일한 소유권을 가진다.
	//자원 획득!
	std::unique_ptr<BigMemory> Ptr = std::make_unique<BigMemory>(500);
	Ptr->DoSomething();
#if 0
	// 복사생성 불가능
	// 로직적으로 옳지 않음
	BigMemory CopyPtr = BigMemory;
#endif // 0

	// 소유권 이전
	// 이동 대입 연산자를 호출하기 위해서 좌측값 Ptr을 우측값으로 타입변환한다.
	std::unique_ptr<BigMemory> MovePtr = std::move(Ptr);
	MovePtr->DoSomething();

#if 0
	// 소유권 이전 확인
	// 소유권을 잃은 객체를 참조하면 런타임 에러가 발생할 것임
	Ptr->DoSomething();
#endif // 0

	// UniqueDoSomething()는 잘 동작함
	// 하지만 의미상으로는 unique_ptr이 유일해야되는데, 
	// 현재 스택과 UniqueDoSomething스택에서 이용할 수 있다.
	// 이렇게되면 유일한 소유권이라는 의미에 맞는건가..?
	UniqueDoSomething(MovePtr);
	// unique_ptr을 래퍼런스로 넘겨주는 것보다 일반 포인터로 주는게 의미상으로 맞다고 본다.
	// 솔직히 const T&로 받아 그냥 참조로만 하는 경우라면 아무래도 상관없지만 그냥 래퍼런스를 받아 수정하는건 좀...
	UniqueDoSomething(MovePtr.get());


} // 자원 반환!

#include <string_view>

class CObject
{
public:
	CObject(std::string_view _Name = "")
		: mName(_Name)
	{

	}

	virtual ~CObject()
	{

	}

	void foo()
	{

	}

private:
	std::string mName;
	
};

// enable_shared_from_this는 객체 내부에 제어블록을 하나 생성하게 됨
// 제어블록은 std::make_shared로 생성
class CSharedObject : public CObject, public std::enable_shared_from_this<CSharedObject>
{
public:
	std::shared_ptr<CSharedObject> GetShared()
	{
		return shared_from_this();
	}

};

#include <vector>
void VectorWithUnique()
{
	std::vector<std::unique_ptr<CObject>> Vec;

	// 임시객체를 넣는 것은 OK
	Vec.push_back(std::make_unique<CObject>());

#if 0
	// 복사 생성으로 전달하는 건 X
	std::unique_ptr<CObject> NewObject = std::make_unique<CObject>();
	Vec.push_back(NewObject);
#endif // 0

	// 이동 시멘틱으로 소유권을 넘기는 경우, 삽입 OK
	std::unique_ptr<CObject> NewObject = std::make_unique<CObject>();
	Vec.push_back(std::move(NewObject));

	// emplace_back은 외부에서 객체를 넘겨주지 않아도 내부에서 객체를 생성해줌
	Vec.emplace_back(std::make_unique<CObject>("Histo"));

	// 객체를 따로 생성하지 않아도 내부에서 기본생성자 call
	Vec.emplace_back();
}

// shared_ptr 하나의 자원을 각 객체가 소유권을 획득해서 관리하는 객체
// 소유권을 공유하는 모든 객체가 존재하지 않을 때, 메모리가 해제된다.
// 내부에서 Ref count를 동기화해야하는데, 그걸 힙에 생성한 제어블록이라는 객체로 관리한다.
void SharedRes()
{
	if (true)
	{
		// 소유권을 갖는 객체 생성
		std::shared_ptr<BigMemory> ObjectA = std::make_shared<BigMemory>(500);
		std::cout << " ============= ObjectA Only  ============= \n";
		std::cout << "ObjectA Ref Count: " << ObjectA.use_count() << '\n';

		// ObjectA가 들고 있는 소유권을 ObjectB가 공유받는다.
		std::shared_ptr<BigMemory> ObjectB = ObjectA;
		std::shared_ptr<BigMemory> ObjectC = ObjectA;
		std::cout << " ============= Get ownership from B to A ============= \n";
		std::cout << "ObjectA Ref Count: " << ObjectA.use_count() << '\n';
		std::cout << "ObjectB Ref Count: " << ObjectB.use_count() << '\n';
		std::cout << "ObjectB Ref Count: " << ObjectC.use_count() << '\n';
	}

	// error code
	if (false)
	{
		// 포인터로 객체를 관리하는 경우, 관리할 자원의 제어블록이 분리될 수 있음
		// 자원의 주소로 소유권을 갖는 객체 생성
		BigMemory* Owner = new BigMemory(500);
		std::shared_ptr<BigMemory> ObjectA(Owner);

		// ObjectA가 들고 있는 소유권을 ObjectB가 공유받는다.
		std::shared_ptr<BigMemory> ObjectB(Owner);
		std::cout << " ============= Get ownership with A and B ============= \n";
		// 레퍼런스 카운트가 각각 1개씩임. 즉, 서로 다른 제어블록을 공유하고 있다. 애초부터 자원을 분리해버렸음
		std::cout << "ObjectA Ref Count: " << ObjectA.use_count() << '\n';
		std::cout << "ObjectB Ref Count: " << ObjectB.use_count() << '\n';
		// ObjectA가 소멸되면서 BigMemory 삭제 
		// ObjectB도 소멸되면서 BigMemory 삭제 
		// double free 문제 발생
	}
}

void EnableShared()
{
	// enable_shared_from_this를 상속받은 객체
	// make_shared 시, 내부에 제어블록이 생성된다.
	std::shared_ptr<CSharedObject> ObjectA = std::make_shared<CSharedObject>();
	// 객체 자신이 가지고 있는 제어블록을 기반으로 소유권을 공유한다.
	std::shared_ptr<CSharedObject> ObjectB = ObjectA->GetShared();

	std::cout << " ============= Get ownership with A and B ============= \n";
	std::cout << "ObjectA Ref Count: " << ObjectA.use_count() << '\n';
	std::cout << "ObjectB Ref Count: " << ObjectB.use_count() << '\n';
}

// 심장 떨리는 코드...
void CircularRefProblem()
{
	std::shared_ptr<BigMemory> ObjectA = std::make_shared<BigMemory>(500);
	std::shared_ptr<BigMemory> ObjectB = std::make_shared<BigMemory>(500);
	ObjectA->SetOther(ObjectB);
	ObjectB->SetOther(ObjectA);

	std::cout << " ============= Get ownership with A and B ============= \n";
	std::cout << "ObjectA Ref Count: " << ObjectA.use_count() << '\n';
	std::cout << "ObjectB Ref Count: " << ObjectB.use_count() << '\n';

	// 자원 반환이 출력되지 않음 그리고 릭도 발생함
	/* otuput:
	자원 획득!
	자원 획득!
	 ============= Get ownership with A and B =============
	ObjectA Ref Count: 2
	ObjectB Ref Count: 2
	*/
}

void CRSolution()
{
	// weak_ptr은 레퍼런스 카운터에 영향을 주지않고 shared_ptr을 참조할 수 있다.
	std::shared_ptr<BigMemory> ObjectA = std::make_shared<BigMemory>(500);
	std::shared_ptr<BigMemory> ObjectB = std::make_shared<BigMemory>(500);
	ObjectA->SetWeakOther(ObjectB);
	ObjectB->SetWeakOther(ObjectA);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		enum 
		{ 
			not_free, 
			not_free_by_Throw, 
			unique_ptr, 
			unique_ptr_with_vec, 
			shared_ptr,
			enable_shared_,
			circular_ref,
			weak_ptr,
		};
		switch (weak_ptr)
		{
		case not_free:
		{
			// 릭
			foo();
			break;
		}
		case not_free_by_Throw:
		{
			// 릭
			bar();
			break;
		}
		case unique_ptr:
		{
			Unique();
			break;
		}
		case unique_ptr_with_vec:
		{
			VectorWithUnique();
			break;
		}
		case shared_ptr:
		{
			SharedRes();
			break;
		}
		case enable_shared_:
		{
			EnableShared();
			break;
		}
		case circular_ref:
		{
			// 릭 발생
			CircularRefProblem();
			break;
		}
		case weak_ptr:
		{
			// 릭 발생
			CRSolution();
			break;
		}
		default:
			break;
		}
	}
	catch (...)
	{
		int a = 0;
	}
}
