// 18_CopyElision.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CObject
{
public:
	CObject(int _Value)
	{
		std::cout << "일반 생성자 호출!" << '\n';
	}

	CObject(const CObject& _Other)
	{
		std::cout << "복사 생성자 호출!" << '\n';
	}
};

int main()
{
	// 일반 생성자, 복사 생성자를 순서대로 호출
	CObject A(5);
	CObject B(A);

	// 복사 생성자로 전달할 인자는 일반 생성자가 호출된 임시객체를 받고 있음
	// 컴파일러 입장에서는 C(5)나 C(CObjcet(5))나 다를게 없다. 
	// 같은 연산이지만 오히려 후자가 더 많은 연산이 발생한다.
	CObject C(CObject(5));
	// output: 일반 생성자 호출!
	// 
	// 컴파일러는 어떻게 복사 생략을 하는지 알 필요가 있다.


    std::cout << "Hello World!\n";
}
