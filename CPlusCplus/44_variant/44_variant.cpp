// 44_variant.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <variant>

// variant는 다수의 타입이 정의된 객체에서 한가지 타입만 저장할 수 있는 객체
// 여러 타입 중, 하나를 one-of 라고 표현
// 내가 A타입일 수도 B 타입일 수도 있다.
// 
// 값 할당 시, 타입이 결정된다.

class Animal
{
public:
	virtual void Bark() = 0;

};

class Dog : public Animal
{
public:
	void Bark() override
	{
		std::cout << "멍멍\n";
	}
};

class Bird : public Animal
{
public:
	void Bark() override
	{
		std::cout << "짹짹\n";
	}
};

using var_pet_type = std::variant<Dog, Bird>;

// variant 내부에 타입을 받는 생성자가 정의되어 있어
// Dog나 Bird를 소유 가능
var_pet_type GetPet(bool _IsDog = true)
{
	if (true == _IsDog)
	{
		return Dog();
	}

	return Bird();
}

int main()
{
	enum
	{
		one_of,
		use_for,
		monostate,
	};

	switch (monostate)
	{
	case one_of:
	{
		// 다수의 타입 중에 int 타입으로 추론됨
		std::variant<int, std::string, double> Value = 1;

		// std::string으로 사용
		Value = "I am String";

		// double로 사용
		Value = 3.3;

		// variant의 사이즈는 가장 큰 객체를 따라간다.
		// 타입 int, char로 정의되어 있을 경우, 가장 큰 size인 int로 할당
		std::variant<int, char> Value2;

		std::cout << "std::variant<int, std::string, double> Size: " << sizeof(Value) << '\n';
		std::cout << "std::variant<int, char> Value2 Size: " << sizeof(Value2) << '\n';

		break;
	}
	case use_for:
	{
		var_pet_type Pet = GetPet();
		// index함수는 템플릿 인자 순서를 반환한다.
		std::cout <<  Pet.index() << '\n';
		/* output: 0 */

		// std::get으로 타입을 뽑아내어 사용
		std::get<Dog>(Pet).Bark();

		break;
	}
	case monostate:
	{
		class A { constexpr A(int) {} };
		class B { constexpr B(int) {} };

#if 0
		// variant 내부에 정의되어 있는 타입들 중에서 디폴트 생성자가 없을 경우,
		// variant는 반드시 객체를 들고 있어야 하므로 컴파일 에러 발생 
		std::variant<A, B> Value0;
#endif // 0

		// variant의 템플릿 인자에 monostate 넣어주면 해결 가능
		// monostate는 아무것도 들어있지 않는 상태

		constexpr std::variant<std::monostate, A, B> Value;

		// 아무것도 들어있지 않을 경우, 
		// 인덱스는 std::monostate를 가리킨다.
		constexpr size_t Index = Value.index(); 

		break;
	}
	default:
		break;
	}
	


}