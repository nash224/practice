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

	// �����Ϸ����� A Ŭ������ �켱 �����Ѵٰ� �˷��ݴϴ�.
	// ���漱���� Ŭ������ ���� Ÿ���� ������, ���������� �����ؾ��Ѵ�.
	class A* mChild = nullptr;
	A& RefChild;
};
