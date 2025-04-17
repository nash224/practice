// EX_Wrapper.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// Wrapper는 객체를(기본타입 포함) '포장'하는 클래스
// 예를 들어, 언리얼에서 제공하는 기본타입 uint8이 wrapper 클래스이다.
class Int
{
	using data_type = int;
public:
	Int(int _Num = 0)
		: Data(_Num)
	{

	}

	Int(const Int& _Other) = default;

	// 타입변환 연산자
	// 리턴타입이 존재하지 않음
	// 연산 기호 자리에 타입이 들어감
	// 기본 타입과 대등하도록 컴파일러에게 알려줌
	operator int() { return Data; }

	// 전위 연산자
	Int& operator++()
	{
		std::cout << "전위 증감 연산자 호출" << '\n';
		++Data;
		return *this;
	}
	Int& operator--()
	{
		--Data;
		return *this;
	}

	// 후위 연산자
	Int operator++(int)
	{
		std::cout << "후위 증감 연산자 호출" << '\n';
		Int Temp = Int(*this);
		++Data;
		return Temp;
	}

	Int operator--(int)
	{
		Int Temp = Int(*this);
		--Data;
		return Temp;
	}

private:
	data_type Data;
};

int main()
{
	// Wrapper 객체 생성
	Int Wrapper = 5;

	// 일반타입(int)과 동일하게 연산 가능
	Wrapper + 87;
	++Wrapper;
	Wrapper++;

    std::cout << "Hello World!\n";
}