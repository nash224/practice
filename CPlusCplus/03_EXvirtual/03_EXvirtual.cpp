// 03_EXvirtual.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class Parent
{
public:
	Parent()
	{
		std::cout << "==== 부모 클래스 생성자 호출 ====" << '\n';
	}

	// 가상함수가 선언되어 있다면, virtual 키워드를 작성해야 한다.
	// virtual은 다형성을 이용하여 같은 이름이여도 다른 동작을 수행하기 위해 선언한다.
	// 이러한 다형성을 이용하다보면 부모 타입의 자식 객체를 소멸할 때, 자식 소멸자가 호출되지 않는 문제가 발생한다.
	~Parent()
	{
		std::cout << "==== 부모 클래스 소멸자 호출 ====" << '\n';
	}

	// virtual 선언 시, 가상함수 테이블이 생성됨
	virtual void foo() const
	{

	}

private:
	
};

class Child : public Parent
{
public:
	Child()
	{
		std::cout << "==== 파생 클래스 생성자 호출 ====" << '\n';
		std::cout << "==== 생성자에서 동적할당 수행 ====" << '\n';
	}

	~Child()
	{
		std::cout << "==== 파생 클래스 소멸자 호출 ====" << '\n';
		std::cout << "==== 소멸자에서 동적할당 메모리 반환 수행 ====" << '\n';
	}

	/* 내부에서 동적할당을 수행합니다. */
	void Alloc(int _Size)
	{
		mPtr;
	}

private:
	int* mPtr = nullptr;
};

int main()
{
	if (false)
	{
		std::cout << "부모 객체 생성" << '\n';
		Parent ParentObject;
	}

	std::cout << '\n';

	if (false)
	{
		std::cout << "자식 객체 생성" << '\n';
		Child ChildObject;
	}

	// 자식 소멸자 호출되지 않는 문제의 예시
	if (true)
	{
		// 동적할당으로 자식객체를 생성하였지만, 받는건 부모 타입
		// 자식 생성자에서 동적할당이 발생했다고 가정
		Parent* pChild = new Child;

		/* do somthind */

		// 사용이 끝난 메모리 해제
		// 부모 포인터 타입으로 메모리 반환할 때 소멸자에 virtual이 없다면
		// 소멸자는 동적바인딩이 되어있지 않고, 컴파일러는 그 존재를 모름
		// 자식 소멸자 호출 x
		if (nullptr != pChild)
		{
			delete pChild;
			/*	==== 부모 클래스 생성자 호출 ====
				==== 파생 클래스 생성자 호출 ====
				==== 생성자에서 동적할당 수행 ====
				==== 부모 클래스 소멸자 호출 ====*/

			// 결과적으로 동적할당한 메모리를 반환하지 않고, 
			// 메모리를 가리키는 포인터를 잃어 댕글링 포인터 발생
			// Leak Memory
			pChild = nullptr;

			// 만약 소멸자에 virtual 키워드를 붙인다면 정상적으로 메모리 해제 작업을 수행한다.
			/*	==== 부모 클래스 생성자 호출 ====
				==== 파생 클래스 생성자 호출 ====
				==== 생성자에서 동적할당 수행 ====
				==== 파생 클래스 소멸자 호출 ====
				==== 소멸자에서 동적할당 메모리 반환 수행 ====
				==== 부모 클래스 소멸자 호출 ====*/
		}
	}

	std::cout << '\n';

}