// 25_CacheLocality.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <chrono>

class Timer
{
public:
	void Start()
	{
		mStartP = std::chrono::high_resolution_clock::now();
	}
	void Stop()
	{
		mEndP = std::chrono::high_resolution_clock::now();
	}

	long long Get()
	{
		std::chrono::duration<double> Duration = mEndP - mStartP;
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(Duration);
		return ms.count();
	}

private:
	std::chrono::high_resolution_clock::time_point mStartP;
	std::chrono::high_resolution_clock::time_point mEndP;

};

constexpr int SIZE = 10000;

// 배열을 반복해서 참조
void foo(int _Arr[SIZE])
{
	int Sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			Sum += _Arr[j];
		}
	}
}

// 배열을 SIZE번 참조 후, 다음 배열을 참조
void bar(int _Arr[SIZE])
{
	int Sum = 0;
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			Sum += _Arr[j];
		}
	}
}

int main()
{
	int Arr[SIZE] = {};
	for (int i = 0; i < SIZE; i++)
	{
		Arr[i] = i;
	}

	Timer t;
	t.Start();
	foo(Arr);
	t.Stop();
	std::cout << "foo() 실행비용: " << t.Get() << '\n';
	t.Start();
	bar(Arr);
	t.Stop();
	std::cout << "bar() 실행비용: " << t.Get() << '\n';
	/* otuput:
	123
	86
	*/

	// 캐시 적중률이 더 높은 bar 함수가 연산비용이 낮다.
	// 캐시 친화적인 코드를 작성해야하는 이유
}
