// 06_DefaultConstructor.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 기본생성자의 이해 및 사용

// 기본생성자 
// 기본생성자는 인자를 전달받지 않는 생성자를 의미합니다.
// 보통 객체를 초기화하거나 객체가 생성될 때 하고 싶은 일이 있을 경우에 사용하빈다.
class DeclareCtor
{
public:
	DeclareCtor()
	{
		std::cout << "기본 생성자 호출" << "\n";
	}

};

class UndeclareCtor
{
public:
	// default 키워드를 사용하면 생성자를 명시적으로 선언할 수 있습니다.
	UndeclareCtor() = default;

	// delete 키워드를 사용하면 생성자를 명시적으로 배제할 수 있습니다.
	UndeclareCtor() = delete;

	// 컴파일러가 기본생성자를 만들어주는지 확인을 위한 복사 생성자 선언
	/* 객체를 복사합니다. */
	UndeclareCtor(const UndeclareCtor& _Other) = default;
	
};

int main()
{
	{
		// 객체를 생성할 때, 명시적으로 선언하는 방식
		DeclareCtor NewObject /*= CObject()*/;
	}

	{
		// 기본 생성자를 선언하지 않아도 빌드가 되는 경우, 
		// 컴파일러가 대신 묵시적으로 생성자를 만들어 줍니다.
		// 
		// 이걸 눈으로 확인하는 방법은 기본 생성자를 선언하지 않고, 
		// 아무 생성자를 만들어 보는 방법이 있습니다.
		// 
		// 이 경우, 컴파일러가 기본생성자를 만들어 주지 않아, 
		// 해당 방법으로 생성할 수 없으므로 컴파일 에러가 발생하게 됩니다.
		UndeclareCtor NewObject;
	}
	

    std::cout << "Hello World!\n";
}