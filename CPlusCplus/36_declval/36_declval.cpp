// 36_declval.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <utility>

// decltype의 쓰임세

class A
{
public:
	int f()
	{
		return 0;
	}

};

// 디폴트 생성자가 존재하지 않는다.
class B
{
public:
	B(int)
	{

	}

	int f()
	{
		return 0;
	}

};


// decltype에 들어갈 식은 컴파일 시간에 실행된다.
// decltype은 문법적으로 옳은 식만 가능
template<typename T>
decltype(T().f()) GetValuef(T& _t)
{
	return _t.f();
}

// std::declval은 생성자로 호출하지 않아도 T타입의 객체를 표현할 수 있다.
template<typename T>
decltype(std::declval<T>().f()) GetValuefUsingDeclval(T _t)
{
	return _t.f();
}


int main()
{
	A a;
	B b(5);

	GetValuef(a);
#if 0
	// GetValuef 함수는 리턴 타입을 추론하기 위해 디폴트 생성자를 사용 하지만,
	// 객체 B에는 디폴트 생성자가 존재하지 않는다.
	GetValuef(b);
#endif // 0

	// 
	GetValuefUsingDeclval(a);
	GetValuefUsingDeclval(b);

#if 0
	// 컴파일 시간에 객체를 표현할 뿐이므로 런타임에서는 실행 불가
	A a2 = std::declval<A>();
	/* console :  error C2338: static_assert failed: 'Calling declval is ill-formed, see N4950 [declval]/2.'
	*/
#endif // 0


    std::cout << "Hello World!\n";
}