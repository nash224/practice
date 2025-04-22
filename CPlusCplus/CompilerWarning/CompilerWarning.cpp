// CompilerWarning.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <functional>

// 컴파일러가 추천한 프로그램을 안전하게 다루는 법
// 컴파일 경고 수준은 최상위로
// 경고를 절대 무시하지 말 것

// 경고 수준 조정하는 법
// 프로젝트 속성 -> c/c++ -> 일반 -> 경고수준 -> 수준4(W4)

class B
{
public:
	virtual ~B()
	{
	}

	virtual void f() const
	{
		std::cout << "call f func\n";
	}

};

class D : public B
{
public:
	virtual void f() const
	{
		std::cout << "call f func\n";
	}
};

int main()
{
	D NewD;
	NewD.f();
    std::cout << "Hello World!\n";
}