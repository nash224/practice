// 16_Overloading.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 오버로딩은 함수의 이름은 같지만, 매개변수의 타입과 개수가 다르게 선언할 수 있는 객체지향의 다형성 개념입니다.
// 

class CMonster
{
public:
	// 생성자도 여러타입의 함수를 선언할 수 있습니다.
	CMonster() {}
	CMonster(const std::string& _Name)
		: mName(_Name)
	{

	}

	void TakeDamage(int _Damage)
	{
		// do something..
	}

	void TakeDamage(int _Damage, bool _DefensePenetration)
	{
		// do something..
	}

	// 리턴 타입이 달라도 오버로딩이 가능합니다.
	int TakeDamge() {}
	// const 도 오버로딩 대상입니다.
	int TakeDamge() const {}

	// 리턴 타입만 다른 프로토타입 선언은 불가능합니다.
	// 리턴 값을 그냥 버리는 경우, 컴파일러가 어떤 함수를 호출할 지 모르기 때문에 오버로딩 대상이 되지 않습니다.
	// bool TakeDamge() {}


private:
	std::string mName;
};

int Add(int, int) { return int(); }

// 특정 타입에 대한 오버로딩을 원치 않을 경우 delete를 붙여 명시적으로 배제할 수 있습니다.
long long Add(long long, long long) = delete;
double Add(double, double) { return double(); }

int main()
{
	int(*IntAddfuncPtr)(int, int) = Add;
	double(*DoubleAddfuncPtr)(double, double) = Add;
	// 오버로딩된 각 함수는 이름만 같을 뿐이지, 다른 주소를 가집니다.
	std::cout << "IntAdd Function Address: " << IntAddfuncPtr << '\n';
	std::cout << "DoubleAdd Function Address: " << DoubleAddfuncPtr << '\n';
	// output:
	//		IntAdd Function Address: 00007FF761471217
	//		DoubleAdd Function Address : 00007FF76147123A
}
