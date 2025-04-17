#pragma once
#include <iostream>

//	���� ��� Ž���� ȣ��� �Լ��� �������� ����� �Լ��� ã�� ������� 
//	���� ��ȿ���� �Ǵ� Ÿ�� T�� ������ �̸� ���� �ȿ��� �켱������ ã��
//	�ٸ� Ÿ�Կ� ���� �̸� ������ Ž���Ѵٴ� ��Ģ�̴�.

// ���� ��� Ž���� ������ �� �ֵ��� �̸�������� ���´�.
namespace widget_stuff
{
	template<typename T> class Widget_impl;

	// Widget Ŭ������ ���� ������ Widget_impl�� �����͸� ������ �ִ� Wrapper Ŭ����
	// Widget_impl�� ������ �������̽��� �����մϴ�.
	template<typename T>
	class Widget
	{
	public:
		Widget() {}
		~Widget() {}

		// ���� ����� �����͸� ��ȯ�մϴ�.
		// ���� ���� ������ �����͸� ���� ������� ��ȯ�� �����մϴ�.
		static void swap(Widget* _A, Widget* _B)
		{
			Widget* Temp = _A;
			_A = _B;
			_B = Temp;
		}

	protected:

	private:
		// �����͸� ��ȯ�ص� �⺻ Ÿ�Կ� ���� ���� ��븸 �߻�
		Widget_impl<T>* mpWidget = nullptr;

	};


	// ���� �������� �Լ��� �����Ͽ� Widget ĸ��ȭ ��ȭ
	
	// �ϰ��� �������̽��� swap�� ������ �� �ֵ���, 
	// std::swap�� ������ �������̽��� �����ϰ�
	// ���ο��� Widget ����� swap �Լ��� �����Ѵ�.
	template<typename T>
	void swap(Widget<T>& _A, Widget<T>& _B)
	{
		std::cout << "���� swap �Լ� ȣ��\n";
		Widget<T>::swap(&_A, &_B);
	}
}

