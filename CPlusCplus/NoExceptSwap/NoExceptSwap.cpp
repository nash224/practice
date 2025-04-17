// NoExceptSwap.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <memory>

#include "Widget.h"

// 복사 비용 테스트용 클래스
class SwapTest
{
public:
	SwapTest() {}
	SwapTest(const SwapTest& _Other)
	{
		std::cout << "복사 생성자 호출!\n";
	}

	SwapTest& operator=(const SwapTest& _Other)
	{
		std::cout << "복사 대입 연산자 호출!\n";
		return *this;
	}

private:

};

template<typename T>
void DoSomething(T& _ObjectA, T& _ObjectB)
{
	// 함수에서 네임스페이스 std를 붙이지 않아도 swap이 호출될 수 있도록
	// using 선언을 해준다.
	using namespace std;
	// ...
	swap(_ObjectA, _ObjectB);
	// std::swap도 호출될 수 있지만, 타입 T의 범위에서 먼저 찾기 때문에 
	// namespace widget_stuff 범위의 swap이 호출된다.
}

int main()
{
#if 0
	SwapTest ObjectA;
	SwapTest ObjectB;
	std::swap(ObjectA, ObjectB);
	/* output:
	복사 생성자 호출!
	복사 대입 연산자 호출!
	복사 대입 연산자 호출!
	*/

	// std::swap 함수 내부에서 복사 비용이 3번 발생
	// 교환 대상이 메모리가 클 수록, 교환단계에서 많은 비용이 발생함  
#endif // 0


	widget_stuff::Widget<int> WidgetA;
	widget_stuff::Widget<int> WidgetB;

	DoSomething(WidgetA, WidgetB);
	/* output: 비멤버 swap 함수 호출 */
}