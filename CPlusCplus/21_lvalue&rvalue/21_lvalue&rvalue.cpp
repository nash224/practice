// 21_lvalue&rvalue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 좌항: 이름이 존재하거나 주소를 얻을 수 있는 값
//  ex) T
// 우항: 좌항이 아닌 것, 상수 또는 임시변수 등, 
//  ex) const T&
// 우측값 참조: 대입 연산자의 오른쪽 값에 대한 참조, 임시 객체를 받을 수 있음
//  ex) T&&

// 좌측값을 참조형으로 받아 수를 증가시킴
void incr(int& _value)
{
    std::cout << "increment with lvalue reference" << "'\n";
    ++_value;
}

// 우측값을 참조형으로 받아 
void incr(int&& _value)
{
    std::cout << "increment with rvalue reference" << "'\n";
    ++_value;
}


// 이동 시멘틱: 객체의 '메모리에 대한' 소유권을 이전하는 것
//	- 보통 컴파일러가 오버헤드를 줄이기 위해 이동 연산자 또는 이동 대입 연산자 메서드를 이용한다.
//	- 이동 대입 연산자 또는 이동 연산자를 정의할 경우 익셉션이 발생하면 안된다.
//	(익셉션 발생 시, 메모리가 정상적으로 소멸되지 않는 이유로 릭이 발생하기 때문)
//	컴파일러에게 익셉션이 발생시키지 않도록 사용자는 noexcept 키워드를 함수 뒤에 붙여 알린다.

class CObject
{
public:
	CObject() {}
	// 이동에 관련된 함수의 핵심은 생성에 대한 오버헤드를 줄여야 한다. 
	// 내부에서 단순복사로 멤버 변수의 메모리에 대한 소유권을 이전시켜야 한다.
	// 원본의 멤버변수 메모리를 새로 생성한 객체로 소유권 이전 후, null처리 
	CObject(CObject&& _other) noexcept = default;			// 이동 생성자
	CObject& operator=(CObject&& _rhs) noexcept = default;	// 이동 대입 연산자
	
};

int main()
{
    int a = 10;
    int b = 20;
    incr(a); // 좌측값 참조형 매개변수에 전달됨 incr(int& _value)

    // a+b의 결과는 우측값
	// 우측값 참조형은 상수를 받을 수 있다.
	int&& c = a + b;
	// 그 인자를 받는 우측값 참조형 매개변수로 전달됨 incr(int&& _value)
    incr(a+b);
	// increment with rvalue reference'

	incr(3);
	// increment with rvalue reference'

	// 이동 시멘틱으로 좌항 변수를 우측값 참조로 변환가능
	incr(std::move(b));
	// increment with rvalue reference'
}
 