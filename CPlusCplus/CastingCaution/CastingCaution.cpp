// CastingCaution.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// c++에서 타입은 컴파일 에러를 방지하기 위한 혜택을 받고 있다.
// 컴파일만 된다면 불안전한 연산을 방지시킬 수 있다.
// 
// 캐스팅은 기존 타입을 다른 타입으로 전환하여 연산을 수행한다.
// 따라서 불안전 캐스팅이 발생할 수 있어서 주의깊게 써야한다.

void Casting()
{
	double Money = 0.0;

	// c 스타일의 캐스트 방식
	auto CStyleCast = (int)Money;

	// 함수 표현 방식 캐스트
	auto FuncCast = int(Money);
	
	// 위 두가지 캐스팅은 '구형 스타일의 캐스트'


	// c++ 은 새로운 형태의 캐스트 방식을 지원한다.
	// 각각의 캐스트 기능은 다음과 같다
	// 
	// 상수성을 없애는 용도
	// const_cast<T>(expr)
	// 
	// 안전한 다운 캐스팅
	// 런타임에 상속 계통에 포함되어 있는 타입 유무 확인
	// dynamic_cast<T>(expr)
	// 
	// 포인터를 int 등으로 바꿀 수 있다.
	// 이식성이 많이 낮아 언어나 os에 종속되는 환경에서만 사용해야 함
	// reinterpret_cast<T>(expr)
	// 
	// 명시적 타입 캐스트 지원
	// int 를 double로 바꾸거나 객체의 타입을 변경할 수 있다. 
	// static_cast<T>(expr)
}

void CreateCodeByCast()
{
	int x, y;
	x = y = 1;

	// int를 double로 변환하여 나눗셈을 수행한다.
	// double / int에 대해서 부동소수점 연산을 수행하기 때문에
	// 캐스트 부분에서 부동소수점으로 바꾸는 코드가 추가된다.
	double result = static_cast<double>(x) / y;
}

// dynamic_cast가 비용이 높은 이유
// c++에서는 dynamic_cast가 문자열 비교를 통해 상속계층인지 알 수 있음
// 즉, 모든 타입 변환이 가능한 모든 클래스 이름 명칭에 대해 strcmp를 수행하는 것
// 가능하면 줄이는게 좋다.


// 캐스팅은 런타임 에러가 발생하는 주요 이유중 하나로 
// 최대한 감추는 것이 좋으며, 함수로 몰아넣어 사용해야 한다.

enum class EObjectOrder
{
	Player,
	Monster,
	BackGround,
};


// 오브젝트를 업데이트 한다.
void Update(int _Order)
{
	// do something...
}

// 타입 캐스팅이 필요한 부분은 템플릿 함수로 묶어 인자를 전달한다.
template<typename EnumType>
inline void Update(EnumType _Order)
{
	// 타입 변환으로 인자를 넘겨준다.
	Update(static_cast<int>(_Order));
}

int main()
{
	// 사용자가 타입 캐스트를 직접 호출하는 것보다
	Update(static_cast<int>(EObjectOrder::Player));

	// 함수 내부에서 캐스팅되도록 지원하는게 좋다.
	Update(EObjectOrder::Player);
}
