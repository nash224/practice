// 33_if_constexpr.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <type_traits>

// if constexpr(x)은 컴파일 시간에 표현식에 만족하는 조건문을 실행한다.
// 타입에 따라 코드의 형태가 달라지는 특성
// 

template<typename T>
void PrintValue(T _t)
{
	// if constexpr이 참이라면 else 구문은 컴파일 되지 않는다.
	// if constexpr의 표현식은 상수식이 와야 한다.
	if constexpr (true == std::is_pointer<T>::value)
	{
		// if constexpr이 아니라면 빌드 단계에서 컴파일 에러가 발생한다.
		std::cout << "Pointer: " << (*_t) << '\n';
	}
	else
	{
		std::cout << "Non-Pointer: " << _t << '\n';
	}
}

int main()
{
	int Value = 3;
	int* Pointer = &Value;

	PrintValue(Value);
	PrintValue(Pointer);
	/* output:
	Non-Pointer: 3
	Pointer: 3
	*/

}