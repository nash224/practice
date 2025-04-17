// 09_functor.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

// functor
// 객체를 함수의 형태로 사용하는 것
// functor는 함수처럼 쓰이기 때문에 메모리를 보유하지 않는다 == 멤버변수를 보유하지 않는다
// 연산자 재정의를 통해 functor 기능 구현

// 내림차순 functor
template <typename T>
class greater
{
public:
	bool operator()(const T& _lhs, const T& _rhs)
	{
		return _lhs > _rhs;
	}

};

// 오름차순 functor
template <typename T>
class lesser
{
public:
	bool operator()(const T& _lhs, const T& _rhs)
	{
		return _lhs < _rhs;
	}
};

// 테스트용 랜덤
// 랜덤 수를 반환합니다. 시드는 고정입니다.
int Seed = 0;
int GenRand()
{
	srand(Seed);
	++Seed;
	return rand();
}

// vector 항목을 교환합니다.
template <typename T>
void Swap(std::vector<T>& _Vec, int _A, int _B)
{
	const T Temp = _Vec[_A];
	_Vec[_A] = _Vec[_B];
	_Vec[_B] = Temp;
}

// 두 번째 인자를 기준으로 정렬을 수행합니다.
template <typename T, typename _Pr = lesser<int>>
void BubbleSort(std::vector<T>& _Vec)
{
	const int SIZE = static_cast<int>(_Vec.size());
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (_Pr(_Vec[i], _Vec[j]))
			{
				Swap(_Vec, i, j);
			}
		}
	}
}

int main()
{
	std::vector<int> Vec;

	const int BUFFER_SIZE = 100;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		Vec.push_back(i);
	}

	for (int i = 0; i < 1000; i++)
	{
		const int A = GenRand() % BUFFER_SIZE;
		const int B = GenRand() % BUFFER_SIZE;

		Swap(Vec, A, B);
	}

	// 템플릿 디폴트 인자로 객체 함수가 전달되어 오름차순 정렬
	BubbleSort(Vec);
	// 템플릿 인자로 객체 함수 타입이 전달되어 오름차순 정렬
	BubbleSort<int, greater<int>>(Vec);

    std::cout << "Hello World!\n";
}