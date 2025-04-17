// 34_decltype.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// decltype은 표현식의 타입을 추론하고 타입으로 치환한다.
// 식별자 표현식(id-expression)이란 연산을 수행하지 않는 객체를 가리키는 식

// decltype은 식별자 표현식에 따라 반환되는 타입이 다름
// 식의 값 종류(value category)가 xvalue일 경우,  T&& 반환
// 식의 값 종류(value category)가 lvalue일 경우,  T& 반환
// 식의 값 종류(value category)가 prvalue일 경우, T 반환

// c++14이후로 추가된 문법
// 리턴 타입을 추론하기 위해 인자 정의 이후에 -> 뒤에 리턴타입 지정
// decltype(_t + _u)은 타입 그대로 치환된다.
template<typename T, typename U>
constexpr auto Add(T _t, U _u) -> decltype(_t + _u)
{
	return _t + _u;
}

int main()
{
	// bool 타입으로 연역
	decltype(5==3) Value = decltype(5 == 3)();

	int a = 6;
	// int로 치환
	decltype(a) b = 5;

	// prvalue 전달
	// (int + int)는 임시객체 int 반환
	decltype(a + b) c = 0;

	// lvalue 전달
	// (a)는 lvalue int& 로 치환
	decltype((a)) d = a;

	const bool IsSameAdress = (reinterpret_cast<__int64>(&a) == reinterpret_cast<__int64>(&d));
	if (IsSameAdress)
	{
		std::cout << "a and b Address same\n";
	}

	// xvalue 전달
	// std::move(a)는 int&&로 치환
	decltype(std::move(a)) e = std::move(a);
	
	// decltype은 auto와 다르게 타입을 그대로 치혼함
	const int NUM = 5;
	auto ValueA = NUM;			// NUM을 받은 auto는 int로 치환
	decltype(NUM) ValueB = NUM; // decltype(NUM)은 const int 로 치환

	// decltype(T, U)이 double로 치환
	const auto Result = Add(3, 5.0);
}