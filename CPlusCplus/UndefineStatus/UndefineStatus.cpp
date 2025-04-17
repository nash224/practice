// UndefineStatus.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 객체가 생성되거나 소멸되는 시점에 가상함수를 쓰면 발생하는 문제

class Transection
{
public:
	Transection()
	{
#if 0
		// 런타임 에러: 
// 내부에서 순수 가상함수 호출
		Init();
#endif // 0

	}

	Transection(const std::string& _Data)
	{
		// 초기화 수행
		_Data;
	}

public:
	void Init()
	{
		GetData();
	}

	// 파생 객체 호출 시, 데이터를 초기화하는 의도함
	// 하지만 부모 클래스 초기화에서 파생 클래스 함수를 사용할 수 없음
	// 결과적으로 정의되어있지 않은 부모의 순수가상함수가 호출되어 런타임 에러 발생
	// 
	// 초기화 시, 데이터를 초기화 수행
	virtual void GetData() = 0;


};

class BankTransection : public Transection
{
public:
	// 이니셜라이저 초기화를 이용하여 부모 클래스에 데이터 전달하는 방법
	// 정적 멤버를 통해 생성자에 전달받은 인자를 이니셜라이저로 전달
	BankTransection(const std::string& _MSG)
		: Transection(BankTransection::CreateData(_MSG))
	{

	}


	void GetData() override
	{

	}

	static std::string CreateData(const std::string& _MSG)
	{
		// 데이터 가공
		return std::string();
	}

};

int main()
{
	BankTransection t{""};

    std::cout << "Hello World!\n";
}
