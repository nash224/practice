// 08_template.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <array>

// 템플릿
// 임의의 타입을 템플릿 매개변수를 통해 정할 수 있게 해 준다.
// 템플릿은 컴파일 시점에 코드를 생성하는 동시에 템플릿에 대한 컴파일도 수행된다.
// 템플릿 선언은 template <typename {type}> 을 클래스나 함수보다 먼저 선언되어야 한다.
template <typename T>
T Add(const T& _A, const T& _B)
{
	return T(_A + _B);
}

// 템플릿 특수화
// 템플릿 매개변수를 특수화하는 것
// 기존 템플릿과 동작하는 일이 다를 때 사용
template <>
bool Add(const bool& _A, const bool& _B)
{
	return _A || _B;
}

// 클래스도 템플릿 선언 가능 
template<typename T>
class Node
{
public:
	const T& Get() const { return mData; }

private:
	T mData;
};

// 템플릿 매개변수를 함수 인자처럼 이용할 수 있음
// 이러한 템플릿에 전달할 인자는 컴파일 시간에 타입이 결정되는 경우만 가능하며, 
// 역시 사용 시점에 코드 생성

// 모든 원소를 출력한다.
template<typename T, int Num>
T Add(T _Num)
{
	return _Num + Num;
}

// 템플릿 클래스에도 템플릿 매개변수를 인자처럼 사용 가능
// MyArray클래스는 컴파일 타임에 크기가 결정됩니다.
template<typename T, int Size>
class MyArray
{
public:
	MyArray()
	{
		
	}

	~MyArray()
	{
	}

	int size() const { return Size; }

private:
	T Arr[Size] = {};

};

int main()
{
	if(false)
	{
		// 템플릿 메서드 호출은 꺽쇠(<>)에 원하는 타입을 넣어줘야 한다.
		// 템플릿이 사용되는 호출 시점에서 코드 생성(템플릿 인스턴스화)
		const bool bResult = Add<bool>(true, false);

		// 유추 가능한 타입에 대한 템플릿 매개변수를 넣어주지 않아도 
		// 컴파일러가 전달받은 인자에 대한 타입을 판단하여 템플릿 인스턴스화를 해 준다.
		const int IntResult = Add(5, 3);
		std::cout << "Hello World!\n";
	}

	if (false)
	{
		const int Result = Add<int, 3>(7);
		std::cout << Result;

	}

	if (true)
	{
		MyArray<int, 10> Arr;
		std::cout << Arr.size();
	}
}