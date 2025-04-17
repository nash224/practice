#pragma once

class A;
class B
{
public:
	B(A* _pObject)
		: RefChild(*_pObject)
	{

	}

	void DoSomething();

	// 컴파일러에게 A 클래스가 우선 존재한다고 알려줍니다.
	// 전방선언한 클래스에 대한 타입은 포인터, 참조형으로 선언해야한다.
	class A* mChild = nullptr;
	A& RefChild;
};
