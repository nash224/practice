// 30_UniformInitialization.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

// 컴파일러는 객체 생성자 호출을 함수의 형태로 잘못보는 경우가 발생한다.
// 

class A
{
public:
	A()
	{
		std::cout << "A 생성자 호출\n";
	}
};

class Int
{
public:
	Int(int _Num = 0)
		: mData(_Num)
	{

	}

private:
	int mData = 0;
};

class Pair
{
public:
	Pair(int, double) {}
	Pair(std::initializer_list<int> _List) {}

};

// only use int and not assign initializer list for test
class Array
{
public:
	// 이니셜라이저 리스트를 받는 생성자
	Array(std::initializer_list<int> _Init)
	{
		for (int i : _Init)
		{
			int a = i;
		}
	}

private:
};


int main()
{
	enum 
	{ 
		uniform_initialization, 
		narrow_conversion, 
		deduce_auto_type, 
		initializer_list, 
		priority_initializer_list
	};

	switch (priority_initializer_list)
	{
	case uniform_initialization:
	{
#if 00
		A a();

		/* otuput:
		*
		* console:
		warning C4930: 'A a(void)': 프로토타입 함수가 호출되지 않았습니다.
		변수 정의로 사용하려고 한 것은 아닌지 확인하십시오.
		*/

		// 아무것도 출력이 되지 않는다. 
		// 컴파일러가 객체 A를 반환값으로 인자가 없는 a함수를 정의하는 것으로 보고 있기 때문이다.

#endif // 0

		// 위와 같은 문제는 균일한 초기화로 해결할 수 있다.
		// c++ 11 부터 생성자의 인자를 () 대신 {}를 사용하여 전달하는 것이 가능하다.

		// 함수 선언하는 형태가 아닌 A 객체를 생성하는 형태
		A a{};

		break;
	}
	case narrow_conversion:
	{
#if 0
		// 유니폼 초기화방식은 암시적 변환을 불허한다.
		// 이때 발생하는 변환은 데이터 손실있는 (Narrowing) 변환이다.
		Int a(3.5); // narrow-conversion 가능
		Int b{3.5}; // narrow-conversion 불가

		/* console:
		warning C4244: '인수': 'double'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.
		error C2398: 요소 '1': 'double'에서 'int'(으)로 변환하려면 축소 변환이 필요합니다.
		*/
#endif // 0

		break;
	}
	case deduce_auto_type:
	{
		// 리턴타입도 자동으로 연역된다.
		auto lamda = [](int, int) -> int { return {}; };
		// 유니폼 초기화로 인자를 전달해주면 매개변수 타입으로 추론되어 전달되어 진다.
		// 유니폼 초기화로 5,3 인자 전달
		lamda({ 5 }, int(3));
		break;
	}
	case initializer_list:
	{
		// 이니셜라이저를 인자로 전달받는 생성자
		// 유니폼 초기화로 이니셔라이저 리스트가 자동 연역된다.
		Array Arr = { 3,5,43 };
		break;
	}
	case priority_initializer_list:
	{
		// 유니폼 초기화로 정수 항목을 받는다면 이니셜라이저 리스트가 최우선으로 선택된다.

		// 벡터 배열 사이즈를 3만큼 늘리는 생성자 호출
		std::vector<int> Vec(3);
		std::cout << "std::vector<int> Vec(3)의 배열 사이즈: " << Vec.size() << '\n';
		// 숫자 3 단일 항목을 받는 벡터 생성자 호출
		std::vector<int> VecB{3};
		std::cout << "std::vector<int> VecB{3}의 배열 사이즈: " << VecB.size() << '\n';

		/* output:
		std::vector<int> Vec(3)의 배열 사이즈: 3
		std::vector<int> VecB{3}의 배열 사이즈: 1
		*/

		Pair PairA(3, 3.5);
#if 0
		// 유니폼 초기화는 손실있는 암시적 변환을 허용하지 않는다.
		Pair PairB{ 3, 3.5 };
#endif // 0

		// 유니폼 초기화로 항목을 받게되면 자동으로 initializer_list가 연역된다.
		auto List = { 5,3,6 };

		std::cout << "auto Type: " << typeid(List).name() << '\n';
		/* output: auto Type: class std::initializer_list<int> */

		break;
	}
	default:
		break;
	}

}
