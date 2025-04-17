// 09_DelegatingCtonstructor.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 위임 생성자
// 생성자의 일부 작업을 다른 생성자에게 위임하는 생성자
// 만들어둔 생성자를 재활용할 수 있다.

struct Int2
{
	// 기본 생성자의 멤버 이니셜라이저 리스트 초기화에서 0, 0을 인자로 받는 생성자를 호출하고 있다.
	// 한 생성자의 작업을 일부 생성자에게 위임하면서 작동이 똑같은 코드를 재활용할 수 있다.
	Int2() : Int2(0, 0)
	{

	}

	Int2(int _X, int _Y)
		: X(_X)
		, Y(_Y)
	{

	}

	int X;
	int Y;
};

int main()
{
    std::cout << "Hello World!\n";
}