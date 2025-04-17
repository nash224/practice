// 22_functional.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <functional>

class CAdd
{
public:
	int operator()(int _A, int _B) { return _A + _B; }
};

int Add(int _A, int _B)
{
	return _A + _B;
}

class Printer
{
public:
	Printer(const std::string& _MSG)
		: MSG(_MSG)
	{
	}

	void Output() const
	{
		std::cout << MSG << '\n';
	}

private:
	std::string MSG;
};

int main()
{
	enum { callable, member_functional, mem_fn, bind };

	switch (bind)
	{
	case callable:
	{
		// callable 이란, 함수 형태로 호출할 수 있는 모든 것

		// function 객체는 템플릿 인자로 함수의 타입을 받음
		std::function<int(int, int)> AddFunc = Add;
		std::cout << "Call Func :" << AddFunc(5, 3) << '\n';

		// functor 객체를 function에 넘겨줄 수 있음
		std::function<int(int, int)> Addfunctor = CAdd();
		std::cout << "Call Functor :" << Addfunctor(5, 3) << '\n';

		// 람다 함수도 받을 수 있음
		auto lamda = [](int _a, int _b) -> int {return _a + _b; };
		std::function<int(int, int)> Addlamda = lamda;
		std::cout << "Call lamda :" << Addlamda(5, 3) << '\n';
		break;
	}
	case member_functional:
	{
		// functional 객체는 멤버함수를 등록하려면 어느 멤버인지 알아야함
		// 멤버함수는 this가 생략되어 어떤 객체의 함수를 호출해야하는지 알 수 있지만
		// functional은 알도리가 없음 
		// 우선 타입만 등록하고 호출 시에 인자로 객체 정보를 넘겨줘야함

		Printer PrintObject("HelloWorld!");
		// 멤버함수를 functional에 등록하는 것은 비멤버 함수를 등록하는것과 다른데, 
		// 멤버함수의 이름을 주소값으로 변환하는건 사용자의 몫이다.
		std::function<void(const Printer&)> OutputFunc = &Printer::Output;

		OutputFunc(PrintObject);
		/*otuput: 
		* HelloWorld!
		*/
		break;
	}
	case mem_fn:
	{
		// std::mem_fn 함수는 함수의 주소를 인자로 functional 객체를 생성해준다.
		Printer Object("call printer::output finction by using mem_fn ");
		std::mem_fn(&Printer::Output)(Object);
		break;
	}
	case bind:
	{
		// std::bind는 특정 인자를 받는 함수객체를 생성해 준다.
		std::function<int(int)> AddWith2 = std::bind(Add, 2, std::placeholders::_1);
		std::cout << "AddWith2(5): " << AddWith2(5) << '\n';

		// 멤버함수를 바인딩하려면, bind 첫번쨰 인자에 멤버함수의 주소값을 넣어줘야 함
		Printer MSG = Printer("Cleared for take-off");
		std::function<void(const Printer&)> PrintMSG = std::bind(&Printer::Output, &MSG);
		PrintMSG(MSG);
		break;
	}
	default:
		break;
	}
}