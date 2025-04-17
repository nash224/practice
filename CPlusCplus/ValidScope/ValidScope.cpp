// ValidScope.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define COVER_SCOPE			0
#define USING_BASE_NAME		1

#define CODE_BRANCH USING_BASE_NAME	

class Base
{
public:
	virtual void mf1() = 0;
	virtual void mf1(int) {}
	virtual void mf2() {}
	void mf3() {}
	void mf3(double) {}

private:
	int x = 0;

};

class Derived : public Base
{
#if CODE_BRANCH == USING_BASE_NAME
public:
	using Base::mf1;
	using Base::mf3;

#endif // CODE_BRANCH
public:
	virtual void mf1(){}

	void mf3() {}
	void mf4() {}

};

int main()
{
	int x = 0;

	Derived D;

	// 이게 진짜 가려지네..
	D.mf1(x);
	D.mf3(x);
}