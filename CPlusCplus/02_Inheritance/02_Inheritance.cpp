// 02_Inheritance.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 상속을 위한 기반 클래스 생성
class Base
{
public:
	Base()
		: mName("기반")
	{
		std::cout << " ==== 기반 클래스 생성자 호출 ====" << '\n';
	}

	// virtual이 하나라도 선언되어 있으면 소멸자에 virtual 키워드 선언
	virtual ~Base() {}

	void what() const
	{
		std::cout << " 기반 클래스 what 멤버함수 호출 " << '\n';
	}

	// virtual: virtual table에 등록시킨다.
	virtual void foo() const
	{
		std::cout << " 기반 클래스 foo 멤버함수 호출 " << '\n';
	}

	// 기반 클래스에서 멤버 접근 허용, 외부 공개 x
protected:
	std::string mName;

};

// 파생 클래스는 기반클래스 정보를 그대로 물려받는다.
class Derived : public Base
{
public:
	// 파생 클래스의 이니셜라이저 리스트에서 기반 클래스 생성자를 먼저 호출한다. 
	// 부모가 생성되고 내가 생성된다.
	Derived()
	{
		// 기본 클래스에서 이미 생성된 멤버에 대한 대입
		// 멤버가 이미 생성되었다. 멤버 이니셜라이저 리스트 이용 불가
		mName = "파생";

		std::cout << " ==== 파생 클래스 생성자 호출 ====" << '\n';
	}

	void what() const 
	{
		std::cout << " 기반 클래스 what 멤버함수 호출 " << '\n';
	}

	// override: virtual 선언된 멤버함수를 명시적으로 재정의하겠다는 명시적 선언
	// virtual table에 등록된 부모의 foo 함수를 재정의
	void foo() const override
	{
		std::cout << " 파생 클래스 foo 멤버함수 호출 " << '\n';
	}

	void DerivedFunction()
	{
		mValue = 5;
		std::cout << "DerivedFunction 호출" << '\n';
	}

private:
	int mValue = 0;

};

// 클래스 정보를 private으로 받음
// 내 다음 파생 클래스에 자신의 부모 멤버 접근 불가
class PrivateDerived : private Base
{
public:
	PrivateDerived()
	{
		// 클래스 내부에서는 부모의 public, protected 멤버 접근 가능
		mName = "Private 파생";
	}

	void bar() const
	{
		std::cout << " private 파생 클래스 bar 멤버함수 호출 " << '\n';
	}
};

class DoublePrivateDerived : private PrivateDerived
{
public:
	DoublePrivateDerived()
	{
		// 부모가 Base 클래스를 private으로 상속받았기 때문에 
		// Base 멤버 접근 불가
		// what();
		// foo();
	}
};

int main()
{
	if (true)
	{
		Base Parent;
		Derived Child;


		Parent.what();
		Child.what();

		// Derived는 Base이다. (Is-A 관계)
		// Derived 포인터는 Base포인터를 가리켜도 무방하다. (Derived 클래스 정보는 보이지 않겠지만)
		// 
		// 기반 클래스로 업캐스팅된 멤버함수를 호출할 경우, 
		// virtual이 선언되지 않았다면 기반 클래스 멤버함수 호출
		// virtual이 선언되었다면 파생 클래스 멤버함수 호출
		Base* pParent = static_cast<Base*>(&Child);
		if (nullptr != pParent)
		{
			// 두 함수의 차이는 클래스의 virtual table 정보에 함수가 등록되어 있는가
			pParent->what();
			pParent->foo();
		}

		if (false)
		{
			// 기반 클래스를 파생 클래스로 다운 캐스팅할 경우, 런타임 에러 발생
			// 기반 클래스는 파생 클래스의 멤버가 존재하지 않는데, 파생 클래스 기능을 사용하려 했음
			Derived* pChild = static_cast<Derived*>(&Parent);
			pChild->DerivedFunction();

			// 컴파일러는 기본적으로 암시적 다운캐스팅을 허용하지 않음
			// Derived* p_p = &Parent;
			// 업캐스팅은 가능
			Base* p_p = &Child;
		}

		// 안전하게 다운캐스팅 하는 방법
		// 다운 캐스팅을 실패하게 되면 nullptr 반환
		Derived* p_c = dynamic_cast<Derived*>(pParent);
		if (nullptr != p_c)
		{
			p_c->what();
		}
	}

	if (false)
	{
		PrivateDerived PrivateChild;
		// 상속받은 클래스 정보를 private으로 받았기 때문에 
		// 기반 클래스의 멤버는 외부에서 접근 불가
		// PrivateChild.what();
		
		// 하지만 자신의 정보는 접근 제한자 그대로 적용
		PrivateChild.bar();
	}

    std::cout << "Hello World!\n";
}