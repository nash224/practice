#pragma once
#include <iostream>

//	인자 기반 탐색은 호출된 함수의 범위에서 가까운 함수를 찾는 방식으로 
//	전역 유효범위 또는 타입 T와 동일한 이름 범위 안에서 우선적으로 찾고
//	다른 타입에 대한 이름 범위를 탐색한다는 규칙이다.

// 인자 기반 탐색을 지원할 수 있도록 이름기반으로 묶는다.
namespace widget_stuff
{
	template<typename T> class Widget_impl;

	// Widget 클래스는 실제 구현된 Widget_impl의 포인터를 가지고 있는 Wrapper 클래스
	// Widget_impl의 동일한 인터페이스를 제공합니다.
	template<typename T>
	class Widget
	{
	public:
		Widget() {}
		~Widget() {}

		// 나와 상대의 데이터를 교환합니다.
		// 실은 실제 구현된 포인터만 복사 방식으로 교환을 수행합니다.
		static void swap(Widget* _A, Widget* _B)
		{
			Widget* Temp = _A;
			_A = _B;
			_B = Temp;
		}

	protected:

	private:
		// 포인터를 교환해도 기본 타입에 대한 복사 비용만 발생
		Widget_impl<T>* mpWidget = nullptr;

	};


	// 비멤버 비프렌드 함수로 선언하여 Widget 캡슐화 강화
	
	// 일관된 인터페이스로 swap을 수행할 수 있도록, 
	// std::swap과 동일한 인터페이스로 선언하고
	// 내부에서 Widget 멤버의 swap 함수를 수행한다.
	template<typename T>
	void swap(Widget<T>& _A, Widget<T>& _B)
	{
		std::cout << "비멤버 swap 함수 호출\n";
		Widget<T>::swap(&_A, &_B);
	}
}

