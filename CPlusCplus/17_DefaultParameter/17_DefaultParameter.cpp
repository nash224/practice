// 17_DefaultParameter.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// c++ 에서 함수의 매개변수에 defualt 값을 지정할 수 있습니다.
// default로 지정된 매개변수를 공란으로 비워둘 경우 default로 지정한 값이 선택됩니다.
int AddNum(int _ValueA, int _ValueB = 100)
{
	int Result = _ValueA + _ValueB;
	std::cout << Result << "=" << _ValueA << "+" << _ValueB << '\n';
	return Result;
}

// 디폴트 매개변수는 우측 인자부터 순서대로 선언해야 합니다.
// 그렇지 않을 경우 컴파일러는 어떤 매개변수가 디폴트 값으로 지정된건지 모릅니다.
// void foo(int _valueA = 100, int _ValueB, int _ValueC) {}

int main()
{
	AddNum(5, 10);
	AddNum(5);
    std::cout << "Hello World!\n";
}
