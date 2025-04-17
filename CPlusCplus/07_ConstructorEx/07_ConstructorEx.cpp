// 07_ConstructorEx.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 목적: 생성자에서 초기화되는 순서를 알아본다.

// 결론
// 객체의 초기화는 재귀적으로 일어난다.
// 멤버 이니셜라이저 리스트 초기화는 바디 초기화보다 우선 순위가 높다.
// 멤버 이니셜라이저 리스트에서 초기화되지 않으면 리터럴 초기화 값을 적용받는다.

class Text
{
public:
	Text(const char* _Str)
	{
		std::cout << _Str << '\n';
	}
	Text(const std::string& _Str)
	{
		std::cout << _Str << '\n';
	}
};

class CObject
{
public:
	CObject(const char* _Str)
		// 1순위 member Initializer List 초기화 
		: mTextA(_Str)
	{
		// 3순위 생성자 바디 초기화
		std::cout << "바디 호출" << '\n';
	}

private:
	// 리터럴 초기화: 멤버 이니셜라이저 리스트에서 초기화되지 않으면 리터럴 초기화 값 적용
	Text mTextB = "리터럴 초기화";
	Text mTextA;
};

int main()
{
	CObject NewObject = CObject("이니셜라이저 리스트 초기화");
    std::cout << "Hello World!\n";
}