// UncopyableClass.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 복사 생성, 복사 대입 연산자를 막는 클래스
class Uncopyable
{
	// 파생 클래스 이외의 외부에서 생성하지 못하도록 막음
protected:
	Uncopyable() {}
	~Uncopyable() {}

	// 복사방지
private:
	Uncopyable(const Uncopyable& _Other);
	Uncopyable& operator=(const Uncopyable& _Other);
};

class Base : public Uncopyable
{
public:
	Base() {}
	~Base() {}

};

int main()
{
	Base BaseA;

#if 0
	// 암시적 복사 생성자를 참조할 수 없다.
	// 삭제된 함수
	Base BaseB = BaseA;
#endif // 0


    std::cout << "Hello World!\n";
}