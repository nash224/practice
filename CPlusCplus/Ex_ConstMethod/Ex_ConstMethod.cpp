
#include <iostream>

class CObject
{
public:
	// 리턴 값의 const 의미 :   타입 앞의 const는 포인터가 가리키는 객체에 대한 멤버변수를 변경하지 않는다
	//                          타입 두의 const는 포인터의 주소 값을 변경하지 않도록 막겠다.
	// 함수의 const 의미 :      메서드 내에서 this가 가리키는 멤버변수를 변경하지 않도록 막겠다.
	// 인자의 const 의미 :      타입 앞의 const는 리턴 값의 const 의미와 동일
	const CObject* const Foo(const CObject* _SpawnObject) const
	{

	}

};

int main()
{
	std::cout << "Hello World";

	return 0;
}