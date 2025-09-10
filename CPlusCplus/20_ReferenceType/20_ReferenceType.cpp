// 20_ReferenceType.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// ================================================
// = Example Helper
// ================================================
#define VAR_NAME(x) #x
#define PRINT_VAR(x) PrintVar(VAR_NAME(x), x);

template <typename T>
void PrintVar(const char* _Name, const T& _Value)
{
    std::cout << _Name << ": " << _Value << '\n';
}

void PrintRegion(const std::string& _RegionName)
{
    std::cout
        << "\n\n===================================\n= "
        << _RegionName
        << "\n===================================\n";
}


// 참조형: 변수에 대한 별명(alias)
// - 이름은 다르지만, 주소 값을 공유한다.
// - 참조를 수정하면 참조가 가리키는 변수의 값도 변경된다.

// 특징
// 참조형 변수는 생성 중에 초기화되어야 한다.
// 초기화 이후, 참조 대상을 변경하지 못한다.

// 장점
// - 표현식이 간단하다.
// - 객체 생성에 대한 비용을 줄일 수 있따.
// - 참조형은 초기화를 강제하므로 런타임에서는 무조건 유효한 변수이다.

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

// 함수가 인자를 받는 방식은 기본적으로 값의 복사본을 받는다. Pass By Value
// 함수의 매개변수를 참조형으로 받게 되면 호출자에서 전달받은 인자의 원본을 받게 된다. Pass By Reference
// 아래의 함수에서는 참조 타입으로 전달받아 값을 서로 교환하고 있다. 
// 참조형으로 전달 받은 매개변수는 인자의 원본이니, 호출자의 값 역시 서로 바뀌게 된다.
void Swap(int& _A, int& _B)
{
    int temp = _A;
    _A = _B;
    _B = temp;
}

// 함수 범위의 지역변수를 참조형으로 리턴하면 안되고 사용해서도 안된다.
// 이런 함수는 컴파일 가능하지만, 에러를 유발하는 코드이다.
// 지역변수는 스택이 종료되는 시점에서 모조리 지워지거나 다른 스택으로 덮어씌워지게 된다.
// 운이 좋으면 정상적으로 받을 수도 있지만, 대부분 덮어씌워진 값을 받을 것이다.
int& ReturnLocalReference()
{
    int ReturnValue = 5;
    return ReturnValue;
}

// warning C4172 지역 변수 또는 임시 : ReturnValue의 주소를 반환하는 중

// 참조형 리턴타입은 이동 시멘틱과 비슷하게 불필요한 복제 비용을 줄일 수 있다.

int& AddedValue(int& _Value)
{
    _Value += 1;
    return _Value;
}

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


    int A = 5;
    int B = 3;
    PrintRegion("Before Swap");
    PRINT_VAR(A);
    PRINT_VAR(B);

    Swap(A, B);
    PrintRegion("After Swap");
    PRINT_VAR(A);
    PRINT_VAR(B);
    
    /*===================================
    =Before Swap
    ===================================
    A: 5
    B: 3

    ===================================
    =After Swap
    ===================================
    A: 3
    B: 5*/

#ifdef _ERROR_CODE
    // 상수를 참조형 매개변수로 받을 수 없음
    swap(3, 4);
#endif // _ERROR_CODE

    std::cout << "retuned local value: " << ReturnLocalReference() << '\n';

    int Level = 3;
    PRINT_VAR(Level);
    // 리턴 타입은 좌항으로 사용 가능
    AddedValue(Level) = 5;
    PRINT_VAR(Level);

}
