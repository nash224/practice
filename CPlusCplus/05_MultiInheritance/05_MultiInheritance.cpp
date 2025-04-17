// 05_MultiInheritance.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class Animal
{
public:
	Animal() {}
	virtual ~Animal() {}

public:
	virtual void Speak()
	{

	}

protected:

	std::string mName;
};

class Mouse : public Animal {};
class Bird : public Animal {};

// c++에서 여러 개의 클래스를 상속받을 수 있도록 지원한다
// 다중 상속할 경우, 상속 받은 멤버를 모두 접근할 수 있다.
// 하지만 다중 상속 시, 해당 클래스처럼 다이아몬드 상속을 하는 경우 
// 멤버의 이용에 있어서 많이 번거로워진다.

class Bat : public Mouse, public Bird
{
public:
	void Speak()
	{
		// Mouse와 Bird는 Animal을 상속받고 있다.
		// mName은 Mouse의 멤버변수이기도 하고 Bird의 멤버변수이기도 한다. 
		// 컴파일러 입장에서는 어느 쪽의 멤버에 접근해야 할 지 모호하다고 판단하여 컴파일 에러를 발생시킨다.
		// mName;
		
		// 범위 지정 연산자로 명시해주면 사용가능 하지만 매번 이러한 방식으로 접근하기에는 너무 번거롭다.
		Mouse::mName;
		Bird::mName;
	}
};

int main()
{
	Bat NewBat;
    std::cout << "Hello World!\n";
}
