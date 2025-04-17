// 04_AbstructClass.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class Abstract
{
public:
	Abstract() {}
	virtual ~Abstract() {}

public:
	// 순수가상함수는 정의되어 있지 않지만, 자식에서 무조건 재정의해야 하는 비어있는 함수
	// 가상함수가 하나라도 존재한다면 그 클래스는 추상클래스라고 한다.
	// 함수 자체가 비어있기 때문에 추상 클래스는 인스턴스를 생성하지 못한다.
	virtual void foo() = 0;

};

class Impl : public Abstract
{
public:
	void foo() override
	{
		std::cout << "무언가를 수행합니다." << '\n';
	}
};

int main()
{
	// 컴파일러에서 왜 비어있는 함수를 가진 개체를 생성하냐고 금지해버린다.
	// Abstract AbstractObject;

	Impl Object;
	Object.foo();
    std::cout << "Hello World!\n";
}