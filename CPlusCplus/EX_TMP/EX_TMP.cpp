// EX_TMP.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 컴파일 시간에 피보나치 수열을 수행합니다.
template<int N>
struct Fibo
{
	static const int Result = Fibo<N - 2>::Result + Fibo<N - 1>::Result;
};

template<>
struct Fibo<0>
{
	static const int Result = 0;
};

template<>
struct Fibo<1>
{
	static const int Result = 1;
};

template<int N>
struct Int
{
	static const int NUM = N;
};

typedef Int<1> ONE;
typedef Int<2> TWO;
typedef Int<3> THREE;

// 컴파일 시간에 더하기 수행 타입 치환
template<typename T1, typename T2>
struct Add
{
	typedef Int<T1::NUM + T2::NUM> Result;
};

// 컴파일 시간에 나누기 수행 타입 치환
template<typename T1, typename T2>
struct Div
{
	typedef Int<T1::NUM / T2::NUM> Result;
};

template<typename N, typename I>
struct PrimeCheck
{
	// 좌측항 성립 시 표현식 우선순위로 치환 중단 >> if(N % I) { return; }
	static const bool Result = (0 == (N::NUM % I::NUM)) 
		|| PrimeCheck<N, typename Add<I, ONE>::Result>::Result;
};

// 템플릿 인자는 단순타입이 아니면 컴파일 불가능
// 즉, N/2는 컴파일 오류 발생
// 해결방안으로 타입 재정의에 의한 치환으로 해결해야 함
// 치환된 타입을 컴파일러가 판단하기 위해서 명시적으로 typename 지정
template<typename N>
struct PrimeCheck<N, typename Div<N, TWO>::Result>
{
	static const bool Result = (0 == (N::NUM % (N::NUM / 2)));
};

template<typename N>
struct _Prime
{
	static const bool Result = (false == PrimeCheck<N, TWO>::Result);
};

template<>
struct _Prime<TWO>
{
	static const bool Result = true;
};

template<>
struct _Prime<THREE>
{
	static const bool Result = true;
};

template<int Num>
struct Prime
{
	static const bool Result = _Prime<Int<Num>>::Result;
};


bool IsPrime(int _Num)
{
	for (int i = 2; i < _Num; i++)
	{
		if (0 == _Num % i)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	Fibo<8>::Result;

	{
		Prime<3>::Result;
		Prime<4>::Result;
		Prime<5>::Result;
		Prime<6>::Result;
		Prime<61>::Result;
		Prime<62>::Result;
	}

    std::cout << "Hello World!\n";
}