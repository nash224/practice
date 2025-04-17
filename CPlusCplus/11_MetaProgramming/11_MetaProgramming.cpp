// 11_MetaProgramming.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 템플릿 코드는 컴파일 시간에 결정되는 특성을 이용하여 
// 코드를 작성하는 것을 메타프로그래밍이라고 한다
// 템플릿 코드를 작성하는 것만큼 런타임 비용이 줄어든다.
// 템플릿은 코드 복사가 일어나기 때문에 실행 파일 크기가 많아진다. 

template<int N>
class Int
{
public:
	// 템플릿을 통한 값 전달이 컴파일 시간에 이뤄지므로 static const에서 초기화 가능
	static const int Num = N;
};

// 컴파일 시간에 덧셈을 수행합니다.
template<typename T, typename U>
struct Add
{
	typedef Int<T::Num + U::Num> Result;

};

// 컴파일 시간에 팩토리얼을 재귀적으로 연산을 수행합니다.
// TMP로 값을 이용할 때는 static const 사용
// 함수를 이용할 때는 typedef 사용
template <int N>
struct Factorial
{
	static const int Result = N * Factorial<N - 1>::Result;
};

// 템플릿 특수화로 1을 전달받는 클래스를 재정의한다.
// 끝을 알리는 함수와 똑같은 개념
template <>
struct Factorial<1>
{
	static const int Result = 1;
};

// 최소공배수를 수행합니다.
template<int X, int Y>
struct GCD
{
	// 재귀 함수에서 재귀 함수 호출부분 return GCD(Y, X % Y); 
	static const int Value = GCD<Y, X% Y>::Value;
};

template<int X>
struct GCD<X, 0>
{
	// 재귀 함수에서 끝을 알리는 부분 if(Y == 0) { return Y; } 
	static const int Value = X;
};

// N은 분자, D는 분모
// 개념상 분모는 0이 될 수 없으므로 디폴트 클래스를 1로 고정
template<int N, int D = 1>
struct Ratio
{
	typedef Ratio<N, D> this_type;

	// 분자
	static const int NUM = N;
	// 분모
	static const int DIM = D;
};

// 템플릿 타입을 받는다. 이때 의도를 확실하게 하기위해서 class를 선언
// T1은 Ratio 클래스를 받음
template<class T1, class T2>
struct _AddRatio
{
	// 타입 치환 특성을 이용하여 유리수 더하기 유도
	typedef Ratio<T1::NUM* T2::DIM + T2::NUM * T1::DIM, T1::DIM* T2::DIM> Result;
};

template<class T1, class T2>
struct AddRatio : _AddRatio<T1, T2>::Result {};


// 함수 타입 재정의
typedef int (*func)(int, int);
using usingFunc = int(*)(int, int);

int Div(int _A, int _B)
{
	return _A / _B;
}

int main()
{
	if (false)
	{
		// 컴파일에 값이 유도가능한 클래스를 타입으로 재정의
		typedef Int<5> Five;
		typedef Int<1> One;

		// 아래 타입은 Int<Five::Num + One::Num> 으로 치환되고,
		// Int<6>이 컴파일 시간에 결정된다. 그걸 Six로 다시 타입 정의
		typedef Add<Five, One>::Result Six;

		// 연속적인 치환으로 인한 템플릿 타입을 상수로 유도하여 
		// 컴파일 시간에 값을 확인할 수 있다.
		const int Result = Six::Num;

		// 컴파일 시간에 15 펙토리얼을 반환받는다.
		Factorial<4>::Result;

		// 컴파일 시간에 최소공배수를 수행한다.
		GCD<36, 24>::Value;

		// 템플릿 메타 프로그래밍식 상수 선언
		typedef Ratio<1, 2> R1;
		typedef Ratio<1, 3> R2;
		typedef AddRatio<R1, R2> R3;
		R3::NUM;
		R3::DIM;
	}

	if(true)
	{
		func DivFunc = Div;
		int DivResult = DivFunc(6, 3);
		std::cout << "typedef Div function's result: " << DivResult << '\n';
		usingFunc DivFuncB = Div;
		DivResult = DivFuncB(6, 3);
		std::cout << "using typedef Div function's result: " << DivResult << '\n';
	}
}