#pragma once
#include <vector>
#include <iostream>

namespace widget_stuff
{

	// ȭ���� ������ �� �ֵ��� gui �������̽��� �������ݴϴ�.
	template<typename Dt>
	class Widget_impl
	{
	public:
		Widget_impl() {}
		~Widget_impl() {}

		Widget_impl(const Widget_impl& _Other)
			: Widgets(_Other.Widgets)
		{
			std::cout << "Widget_impl ���� ������ ȣ��!\n";
		}

		Widget_impl& operator=(const Widget_impl& _Other)
		{
			Widgets = _Other.Widgets;
			std::cout << "Widget_impl ���� ���� ������ ȣ��!\n";
		}

	protected:

	private:
		//  Ư�� ������ �����Ѵ�.
		std::vector<Dt> Widgets;

	};

}