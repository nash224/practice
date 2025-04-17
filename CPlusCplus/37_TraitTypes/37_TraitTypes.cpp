// 37_TraitTypes.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// trait_types 라이버러리에는 함수가 존재하지 않고 
// 템플릿 인자를 전달받아 연산을 수행하는 
// 템플릿 메타 함수의 집합으로 이루어져 있다.

template <typename T>
struct is_void
{
	static constexpr bool value = false;
};

// 템플릿 특수화 bool 타입이 템플릿 인자로 전달되면 
// 템플릿 특수화로 인스턴싱된다.
template <>
struct is_void<void>
{
	static constexpr bool value = true;
};

template <typename T>
void PrintIsVoidType()
{
	if (is_void<T>::value)
	{
		std::cout << "The type passed is void.\n";
	}
	else
	{
		std::cout << "The type passed isn't void.\n";
	}
}

class A
{

};

class B : public A
{

};

struct Int
{
public:
	Int(int Data = 0)
		: Data(Data)
	{

	}

public:
	int Data;
};



int main()
{
	PrintIsVoidType<int>();
	PrintIsVoidType<void>();
	/* otuput:
	The type passed isn't void.
	The type passed is void.
	*/

	int Value = 0;
	int* Ptr = &Value;
	// trait_types 라이브러리 함수 예시
	constexpr bool Isvoid = std::is_void_v<void>;
	constexpr bool IsPointer = std::is_pointer<decltype(Ptr)>::value;
	constexpr bool IsPointerB = std::is_pointer<decltype(Value)>::value;
	constexpr bool IsObject = std::is_object<decltype(Value)>::value;
	constexpr bool IsBase = std::is_base_of<A, B>();

	// 템플릿 인자가 클래스일 경우, 참의 값 반환
	constexpr bool IsClass = std::is_class<A>();
	
	Int nObject = 5;

	// Int의 멤버 변수를 가리키는 포인터
	int Int::* pData = &Int::Data;

	// 멤버변수 포인터로 nObject의 변수 참조
	nObject.*pData;

	std::cout << "nObject.Data: " << nObject.Data << '\n';
	std::cout << "nObject.*pData: " << nObject.*pData << '\n';
	// 객체가 아니더라도 무조건 값을 가진다.
	std::cout << "pData: " << pData << '\n';
	/* output:
	nObject.Data: 5
	nObject.*pData: 5
	pData: 1
	*/

	// T::* 가 

#if 0
	// 기본 타입에 대한 변수를 가리키는 포인터는 불가능
	// 클래스와 일반 타입의 차이점으로 클래스인지 판단한다.
	int int::* DataPointer;
#endif // 0

} 




