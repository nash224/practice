// 02_const.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

const std::string message = "test";

const std::string& foo()
{
    return message;
}

int main()
{
    if (false)
    {
        auto Result = foo();
        const auto& ConstResult = foo();
        std::cout << ConstResult << "\n";
    }

    if (true)
    {
        decltype(foo()) reuslt = foo();
        std::cout << &reuslt << "\n";
        std::cout << &message << "\n";
    }

    if (false)
    {
        decltype(auto) reuslt = foo();
        // 같은 주소를 반환한다. 즉, const std::string& 으로 연역된다.
        std::cout << &reuslt << "\n";
        std::cout << &message << "\n";
    }
	// ah
}