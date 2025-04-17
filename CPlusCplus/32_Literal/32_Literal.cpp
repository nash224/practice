// 32_Literal.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 리터럴 타입은 컴파일러가 컴파일 타임에 정의할 수 있는 타입이다.
// 종류는 void, 스칼라, 리터럴 배열, constexpr로 정의된 함수(생성자 소멸자)를 가진 클래스 등이 있다.
// c++ 14부터 constexpr 생성자로 리터럴 객체를 지원한다.

// constexpr 생성자 사용 시, 제약사항
//		- constexpr 함수에 적용되는 제약조건 적용
//		- 생성자에 전달 받는 인자는 모두 리터럴타입
//		- 가상 상속 불가

// 좌표 표현에 사용될 int타입을 2개 받는 구조체
struct Int2
{
public:
	// 사용자 정의 리터럴 타입 클래스의 멤버함수는 모두 constexpr 함수로 정의되어야 함
	constexpr Int2(int _X = 0, int _Y = 0)
		: X(_X)
		, Y(_Y)
	{

	}

	// constexpr은 디폴트 소멸자로 선언되어야 함
	// 따라서 컴파일러가 대신 만들어주니 굳이 명시할 필요 x
	// ~Int2();

	constexpr Int2& operator+=(const Int2& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return (*this);
	}

public:
	int X;
	int Y;

};

// 비상수식 함수가 아니라면 런타임에 연산
constexpr inline Int2 operator+(const Int2& _lhs, const Int2& _rhs)
{
	// 유니폼 초기화로 객체생성
	return Int2{ _lhs.X + _rhs.X, _lhs.Y + _rhs.Y };
}

template<int N>
struct Int
{
	operator int(){ return N; }
};

int main()
{
	// 컴파일 타임에 값확인 가능 
	constexpr Int2 Coord_A = Int2(1, 2);
	constexpr Int2 Coord_B = Int2(3, 4);

	// 컴파일 타임에 좌표 더하기 연산
	constexpr Int2 Coord_C = Coord_A + Coord_B;

	// Coord_C.X은 정수 상수식으로 템플릿 인자에 전달 가능
	Int<Coord_C.X> Value;

    std::cout << "Print Int<Coord_C.X> Value: " << Value << "\n";
}