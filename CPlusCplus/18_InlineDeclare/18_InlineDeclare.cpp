// 18_InlineDeclare.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CMonster
{
public:
	// inline은 호출된 스택에 함수의 바디를 삽입하여 호출 오버헤드를 줄이겠다는 선언입니다.
	// 이걸 인라인화라고 합니다.
	// 
	// 여기서 의문이 생깁니다.
	// inline 선언으로 호출 오버헤드를 줄이겠다고 모든 함수에 inline 선언을 붙이는 것입니다.
	// 
	// 인라인은 함수가 복잡할 경우 오히려 오버헤드를 발생시킵니다.
	// 이런 함수에 inline이 선언되어 있을 경우, 컴파일러는 inline을 무시해버립니다.
	// 반대로 성능이 좋은 함수에 대해 inline선언을 해 줍니다.
	// 
	// 
	// inline 선언 방법은 함수 프로토타입 앞에 inline 키워드를 붙이면 됩니다.
	// 보통 inline 함수 정의는 헤더파일에 위치합니다.
	inline const std::string& GetName() const
	{
		return mName;
	}

private:
	std::string mName;
};

int main()
{
    std::cout << "Hello World!\n";
}
