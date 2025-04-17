// EX_CallByReference.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 목적: 값에 의한 전달과 참조에 의한 전달의 성능 비교와 어떤 상황에서 사용되는 지 이해해 본다.

#include <iostream>
#include <chrono>

// 값에 의한 전달(Call By Value)
// 함수를 호출할 때, 매개변수를 값 형태로 전달받는 방식
// 
// 특징
// 원본 객체에 대한 수정이 이루어 지지 않는다.
// 복사 생성자가 일어난다.

class Timer
{
	using clock_type = std::chrono::high_resolution_clock;
	using time_type = std::chrono::nanoseconds;

public:
	void Start()
	{
		_now(STime);
	}

	void Stop()
	{
		_now(ETime);
	}

	void PrintTime() const
	{
 		std::chrono::duration<double> Result = ETime - STime;
		time_type sec = std::chrono::duration_cast<time_type>(Result);
		std::cout << "실행 시간: " << sec.count() << '\n';
	}

private:
	void _now(clock_type::time_point& _Time) const
	{
		_Time = clock_type::now();
	}

private:
	clock_type::time_point STime;
	clock_type::time_point ETime;
	
};

// 단순 더미 데이터
struct Dummys
{
	using size_type = long long;

	size_type Arr[100] = {};
};

class CObject
{
public:

private:
	// 이런 더미를 여러개 가지고 있다.
	Dummys Arr[10];
};

// 성능 방지코드
template <typename T>
void dosomething(const T& _Object, bool _Value = false)
{
	if (_Value)
	{
		_Object;
	}
}

// 인자를 값에 의한 전달로 받음
template <typename T>
void CallbyValue(volatile T _Object)
{
	// use
	dosomething(_Object);
}

// 인자를 참조에 의한 전달로 받음
template <typename T>
void CallbyReference(volatile const T& _Object)
{
	// use
	dosomething(_Object);
}

int main()
{
	CObject NewObject;
	Timer TimerObject;

	{
		TimerObject.Start();
		CallbyValue(NewObject);
		TimerObject.Stop();

		std::cout << "CallbyValue" << '\n';
		TimerObject.PrintTime();
		// 실행 시간: 17100
	}

	{
		TimerObject.Start();
		CallbyReference(NewObject);
		TimerObject.Stop();

		std::cout << "CallbyReference" << '\n';
		TimerObject.PrintTime();
		// 실행 시간: 200
	}

	// 위 실험 결과로 80배의 성능차이가 발생했다.
	// CallByValue 방식은 객체를 생성해서 인자로 넘겨주게 되는데, 
	// 객체의 메모리 생성 및 소멸 비용이 발생하게 된다.
	// 전달받을 객체의 비용이 클 수록 할당 및 반환비용이 많이 발생한다.

	// 결론: 원본 객체를 복사할 일이 없다면 Call By Reference 형태로 전달해야 한다.


    std::cout << "Hello World!\n";
}