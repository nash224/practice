// 20_ReferenceType.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 참조형: 변수에 대한 별명(alias)
// - 이름은 다르지만, 주소 값을 공유한다.
// - 참조를 수정하면 참조가 가리키는 변수의 값도 변경된다.

// 특징
// 참조형 변수는 생성 중에 초기화되어야 한다.
// 초기화 이후, 참조 대상을 변경하지 못한다.

#define _ERROR_CODE_MODE 0

#if _ERROR_CODE_MODE
#define _ERROR_CODE
#endif // _ERROR_CODE_MODE

// 이전 스택의 변수를 참조한다.
// Pass by reference
template <typename T> 
void PrintAddress(std::string _Title,T& _Value)
{
    std::cout << _Title << " Address:" << reinterpret_cast<__int64>(&_Value) << '\n';
}

class HaveReferenceClass
{
public:
#ifdef _ERROR_CODE
    // 참조형 변수는 무조건 초기화되어야 하므로 컴파일되지 않는다.
    HaveReferenceClass() {}
#endif // _ERROR_CODE

    HaveReferenceClass(int& _Ref) : mRef(_Ref) {}

    // 참조형 멤버변수는 클래스가 인스턴스화되는 시점에서 초기화되어져야 한다.
    int& mRef;
};

int main()
{
    int x = 0, y = 0; 
    int& xRef = x; // xRef는 x를 참조한다. xRef 변수가 변경되면 x도 동일한 값으로 변경된다.
    xRef = y; // 초기화된 xRef는 사실상 x와 동일하기에 y 값을 대입받는다.

    std::cout << "x Address: " << reinterpret_cast<__int64>(&x) << '\n';
    std::cout << "xRef Address: " << reinterpret_cast<__int64>(&xRef) << '\n';
    // 둘 다 동일한 주소
    // x Address : 517805439396
    // xRef Address : 517805439396

#ifdef _ERROR_CODE 
    // 초기화되지 않은 참조형 변수는 애초부터 컴파일도 못하게 막아뒀다.
    int& EmptyRef; 
#endif // _ERROR_CODE 

    // 이름 없는 값이라도 constT&로 참조 가능
    const int& rvalueRef = 10;

#ifdef _ERROR_CODE
    // const가 아닌 숫자는 참조할 수 없다.
    int& UnnamedRef = 5

#endif // DEBUG

    // T가 어느 타입이라도 참조 가능
    int* Ptr = 0;
    // 포인터 타입에 대한 참조
    int*& PtrRef = Ptr;

    PrintAddress("Ptr", Ptr);
    PrintAddress("PtrRef ", PtrRef);
    // Ptr:506641511912
    // PtrRef : 506641511912
    // 주소 값이 일치한다.
}