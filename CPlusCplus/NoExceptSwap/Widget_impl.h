#pragma once
#include <vector>
#include <iostream>

namespace widget_stuff
{

	// 화면을 조작할 수 있도록 gui 인터페이스를 제공해줍니다.
	template<typename Dt>
	class Widget_impl
	{
	public:
		Widget_impl() {}
		~Widget_impl() {}

		Widget_impl(const Widget_impl& _Other)
			: Widgets(_Other.Widgets)
		{
			std::cout << "Widget_impl 복사 생성자 호출!\n";
		}

		Widget_impl& operator=(const Widget_impl& _Other)
		{
			Widgets = _Other.Widgets;
			std::cout << "Widget_impl 복사 대입 연산자 호출!\n";
		}

	protected:

	private:
		//  특정 정보를 포함한다.
		std::vector<Dt> Widgets;

	};

}