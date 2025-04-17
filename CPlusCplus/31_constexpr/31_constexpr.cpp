// 31_constexpr.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// constexpr은 상수식을 명시해주는 키워드이다.
// 객체나 함수 앞에 constexpr을 붙이면 컴파일 시간에 값이나 타입을 확인할 수 있다.
// constexpr은 대부분 상수식으로 표현되는데, 
// 상수식(constant expression)은 컴파일러가 컴파일 타임에 값을 알 수 있는 표현식이다.
// 정수 상수식(Integral constant expression)은 상수식이 정수 값을 가진 표현식이다.

// 팩토리얼 연산을 컴파일 시간에 수행합니다.
int NonConstexpr();
constexpr int Factorial(int _N);

int main()
{
	enum 
	{
		Interal_constexpr,
		constexprVSconst,
		constexprFunction
	};
	switch (constexprFunction)
	{
	case Interal_constexpr:
	{
		// 컴파일 시간에 확인할 수 있으면 상수식
		const int SIZE = 5;
		// 정적 배열의 크기는 정수 상수식만 받을 수 있다.
		int Arr[SIZE] = {};

		const int ONE = 1;
		// enum 항목에 값은 정수 상수식만 허용한다.
		enum { a = ONE, b };

		break;
	}
	case constexprVSconst:
	{
		// 상수에 리터럴을 넣어주면 컴파일 시간에 결정되는 상수식이 된다.
		// 컴파일 시간에 값 확인 가능
		const int CONST_VALUE = 5;

		// 런타임에 값이 결정되는 변수 선언
		int Value = 3;
		// 그걸 상수가 받게 될 경우, 런타임에서 결정되는 상수가 된다.
		// ConstVar은 CONST_VALUE 와 다르게 컴파일 시간에 값을 알 수 없다.
		const int ConstVar = Value;

#if 0
		// constexpr은 상수식을 표현하는 문법으로 런타임에 결정되는 표현식은 대입할 수 없다.
		// 컴파일 조차 되지 않는다.
		constexpr int c = Value;
#endif // 0

		break;
	}
	case constexprFunction:
	{
		// 컴파일 시간에 값 확인 가능
		// constexpr을 리턴값에 붙이면, 컴파일 시간에 연산되어 상수식으로 반환된다.

		std::cout << Factorial(5) << '\n'; ;
		/* output: 120 */


		int Five = 5;

		// constexpr 함수에 사용될 인자가 상수식일 경우, 컴파일 타임에 연산되면 상수식으로 반환되고,
		// 비상수식일 경우, 런타임에 연산되어 비상수식이 반환된다.
		const int Result = Factorial(Five);
		std::cout << Result << '\n';
		/* output: 120 */
		break;
	}
	default:
		break;
	}
	
}

int NonConstexpr() { return 0; }

constexpr int Factorial(int _N)
{
	int Total = 1;
	for (int i = 1; i <= _N; i++)
	{
		Total *= i;
	}

#if 0
	// constexpr 함수에서는 Non-constexpr 함수를 호출할 수 없다.
	NonConstexpr();
#endif // 0


	return Total;
}
