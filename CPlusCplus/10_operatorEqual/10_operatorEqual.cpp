// 10_operatorEqual.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CObject
{
public:
	CObject() = default;

	// 대입 연산자
	// 객체의 값을 자신한테 덮어씌울 떄, 호출되는 함수
	// 연산자 오버로딩을 통해 재정의가 가능하다.
	// 
	// 객체 내부의 멤버 변수는 대입연산자를 재귀적으로 호출
	// 
	// 리턴 값으로 자신의 참조형을 반환한다.

	CObject& operator=(const CObject& _Other)
	{
		// 자기 자신을 대입받는 것은 옳지 않다.
		if (this == &_Other)
		{
			return;
		}

		Text = _Other.Text;
		mSize = _Other.mSize;
	}

	// delete 키워드를 붙일 경우, 명시적으로 배제한다.
	CObject& operator=(CObject && _Other) noexcept = delete;

public:
	std::string Text;
	int mSize = 0;
};

int main()
{
	CObject AObject;
	CObject BObject;
	BObject.Text = "Hello World!";

	AObject = BObject; // AObject.operator=(BObject) 와 똑같다.


    std::cout << "Hello World!\n";
}
