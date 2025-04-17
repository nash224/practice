// 35_ValueCategory.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// c++ 식은 타입과 값 카테고리(value category) 두가지 타입으로 표현된다.
// 값 카테고리는 좌측값, 우측값을 포함한 5가지로 나태낼 수 있다.

// 값 카테고리는 주소를 취할 수 있는지, 이동시킬 수 있는지로 구분
// 분류하면 다음과 같다.
//							이동시킬 수 있다.	이동시킬 수 없다.
//	정체를 알 수 있다.		xvalue				lvalue
//	정체를 모른다.			pravlue				x

// glvalue	:	정체를 알 수 있는 모든 식
// rvalue	:	이동할 수 있는 모든 식

int main()
{
	enum
	{
		lvalue,
		prvalue,
		xvalue,
	};
	switch (lvalue)
	{
	case lvalue:
	{
		// lvalue
		// 주소를 얻을 수 있으며, 이동할 수 없다. 
		// 이동할 경우 std::move로 우측값 변환하여 전달
		int i = 0;

		std::cout; // 변수, 함수, 멤버변수는 좌측값

		auto lamda = [](int& _Other) -> int& { return _Other; };
		lamda(i);	// 좌측값 레퍼런스를 리턴하는 함수 호출식도 좌측값
		const char* Str = "문자열 리터럴"; // 문자열 리터럴도 좌측값
		const __int64 Address = reinterpret_cast<__int64>(&Str); // 주소값을 취할 수 있다. 즉, 좌측값

		int&& r_r = std::move(i);

#if 0
		// 좌측값은 우측값 레퍼런스에 대입 불가
		int&& r_l = i;
#endif // 0

		int&& r_r = std::move(i); // 우측값 레퍼런스는 좌측값 

		// 우측값 레퍼런스는 주소를 취할 수 있다.
		int* pr_r = &r_r;

		break;
	}
	case prvalue:
	{
		int a = 0;

#if 0
		// prvalue
		// 이름을 없으면서 우측값 레퍼런스에 대입 가능한 것
		// rvalue는 좌측값에 올 수 없다.
		prvalue = ;
		// 주소도 취할 수 없다.
		&42;

#endif // 0
		auto lamda = []() -> int { return 0; }; // 람다식 자체도 우측값
		// lamda()는 주소를 취할 수 없지만, 이동은 가능하다.
		// 이를 임시 객체라고 부르며, 우측값 레퍼런스로 받을 수 있다.
		int&& rr = lamda();

#if 0
		// 우측값을 좌측값의 레퍼런스로는 받을 수 없다.
		int& lr = lamda();
#endif // 0

		// rvalue 종류
		42, true;                               // 문자열 리터럴이 아닌 모든 값. 주소를 취할 수 없다.
		lamda();                                // 임시 객체 반환

		(lamda() < rr);                         // 산술 연산자 등도 임시객체. 반환 bool도 객체니까
		&a;	                                    // 주소값 연산자 식. 이것도 주소값을 반환하니까
		auto&& Evalue = prvalue;                // enum 값도 우측값 레퍼런스로 받을 수 있으니 우측값

		// 상수 좌측값 레퍼런스 초기화로 우측값 사용 가능
		const int& Cl_r = 42;

		break;
	}
	case xvalue:
	{
		int i = 0;

		{
			// xvalue
			// 우측값 레퍼런스를 리턴하는 함수 호출식
			// 유효한 블록의 범위가 아니게 되면 i는 소멸한다.
			// 그 전까지 이동이 가능하고 주소를 취할 수 있다.
			int&& rr = move(i);
		}
		break;
	}
	default:
		break;
	}
	
}

class A
{
public:
	void foo()
	{
		// this: 주소를 취할 수 없고, 자신의 주소를 던져주니 rvalue
		A* pA = this;
	}
};

template<typename T>
constexpr inline typename std::remove_reference<T>::type&& move(T&& _t) noexcept
{
	return (_t);
}
