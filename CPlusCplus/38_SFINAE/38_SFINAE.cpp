// 38_SFINAE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <utility>

// SFINAE원칙: 치환 오류는 컴파일 오류가 아니다.
// 템플릿 인자가 치환된 후, 문법적으로 옳지 않을 경우 오버로딩 후보군에서 제외시킨다.
// 컴파일러는 인자 타입, 리턴타입이 불일치할 경우 컴파일 에러를 발생시킨다.

// 클래스에 정의되어 있는 타입을 전달받는다.
// T클래스의 x타입
template <typename T>
void DoSomething(typename T::x _a)
{
	std::cout << "T::x \n";
}

// T클래스의 y타입
template <typename T>
void DoSomething(typename T::y _a)
{
	std::cout << "T::y \n";
}

// std::enable_if는 템플릿 인자가 특정 조건식에서 false일 때, 컴파일 에러를 발생시킨다.
template <typename T
	, typename = typename std::enable_if<std::is_integral<T>::value>::type>
void IntCheck(T _Type)
{
	std::cout << _Type << '\n';
}

// c++ 14부터 std::enable_if 축약형으로 std::enable_if_t 버전을 제공한다.
// std::enable_if_t는 단순 타입 ailas 버전이다.
template <typename T, typename = typename std::enable_if_t<std::is_object_v<T>>>
void ObjectCheck(T _Type)
{
	std::cout << _Type << '\n';
}

// 컴파일 타임에 std::declval<T>()로 더미 객체를 만들어서 멤버 함수가 있는지 확인
// func라는 멤버 함수가 없을 경우, 컴파일 에러 
template<typename T, typename = decltype(std::declval<T>().func())>
void CallA(const T& _Object)
{
	std::cout << "CallA\n";
}

// 리턴타입 int를 반환하는 funB 멤버함수가 있는 객체를 받도록 제한한다.
template<typename T
	, typename = typename std::enable_if_t<
	std::is_integral_v<decltype(std::declval<T>().funcB())>>>
void CallAfuncBWithReturnInt(const T& _)
{
	std::cout << "CallAfuncBWithReturnInt\n";
}

class A
{
public:
	using x = int;

	void func() {}
	int funcB() { return 0; }
};

class B 
{
public:
	using y = int;

};

int main()
{
	DoSomething<A>(55);

	// B클래스가 타입 T::x을 받는 함수에 호출받으면 B::x 타입으로 치환된다.
	// 문법상으로 옳지 않지만, 컴파일러는 오버로딩 후보군에서 제외시켜 
	// 컴파일 오류를 발생시키지 않는다.
	DoSomething<B>(22);

	// 전달해준 인자 타입이 정수라면 ok
	IntCheck(false);
	IntCheck(5);
#if 0

	// 오브젝트일 경우, x 컴파일 불가
	IntCheck(A{});
#endif // 0

	// A 함수에 func 멤버함수가 있어서 ok
	CallA(A{});

#if 0
	// B 함수에 func 멤버함수 없어서 NG
	CallA(B{});
#endif // 0

	// A에 int를 반환하는 funB가 있으므로 OK
	CallAfuncBWithReturnInt(A{});


}