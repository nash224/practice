// Interface&ImplementInheritance.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <memory>

class Food {};

class Person
{
public:
	virtual ~Person() {}

public:
	// 무언가를 동작합니다.
	// 순수 가상으로 선언하여 인터페이스만 상속해준다
	// 가상으로 선언되어 있기 때문에, 책임은 물려받은 쪽으로 전담한다.
	virtual void Act() = 0;

	// 무언가를 먹는다.
	// 기본 동작을 제공하되, 필요 시 재정의할 수 있도록 인터페이스와 구현을 상속한다.
	// 기본 동작으로부터 발생하는 책임은 물려주는 쪽이 줘야 하므로 주의를 기울여야 한다.
	virtual void Eat(Food)
	{

	}

	// 비가상 함수 
	// 인터페이스 상속과 더불어, 필수적인 동작을 수행하는 구현을 상속
	void Think()
	{

	}

protected:
	// 동작은 Person::Act 함수와 동일
	// protected로 파생 클래스에서만 접근 허용하도록 하며,
	// 비가상 함수로 선언하여 기본에서 제공하는 함수라고 명시
	void DefaultAct()
	{
		std::cout << "팔이라도 움직인다.\n";
	}
};

// 순수 가상으로 선언되어 있지만, 기본 구현은 OK
void Person::Act()
{
	std::cout << "팔이라도 움직인다.\n";
}

class Dancer : public Person
{
public:
	// 물려받은 인터페이스를 재정의한다.
	virtual void Act() override
	{
		// 순수 가상 함수 인터페이스라도, 
		// 명시적으로 사용할 경우 사용 가능
		Person::Act();
		// DefaultAct();
	}
};

int main()
{
	std::unique_ptr<Dancer> NewDancer = std::make_unique<Dancer>();
	// 어쩃든 팔이라도 움직인다.
	NewDancer->Act();

    std::cout << "Hello World!\n";
}
