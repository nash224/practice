// 12_auto.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

int Sum(int A, int B) { return A + B; }

class Int
{
public:
	Int(int _Value)
		: mData(_Value)
	{

	}

	operator int() { return mData; }

private:
	int mData;
};

int main()
{
	// 컴파일러는 타입을 명시하지 않아도 추론할 수 있다.
	// auto는 컴파일러에게 타입을 추론하라고 지시하는 키워드이다.
	auto Value = 3;
	auto SumValue = Sum(Value, 3);

	auto fValue = 0.3f + 1.2f;

	auto IntValue = Int(4);
	auto CloneInt = IntValue;

	const char* const Str = typeid(Value).name();

	// 타입을 알아내서 문자열로 반환하는 함수
	// typeid(Value).name();
	std::cout << "what is type 'Value'? : " << typeid(Value).name() << '\n';
	std::cout << "what is type 'CloneInt'? : " << typeid(CloneInt).name() << '\n';

}