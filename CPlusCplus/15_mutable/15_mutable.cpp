// 15_mutable.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>


class CMonster
{
public:

	// 몬스터의 이름을 반환합니다.
	const std::string& GetName() const // const 선언 : 멤버 변수에 대한 변경을 허용하지 않겠다.
	{
		++CallCount; // mutable 멤버변수에 대한 수정 코드
		std::cout << "Call Count: " << CallCount << '\n';
		return mName;
	}

private:
	// const 함수에서 멤버변수를 변경할 수 없다고 알고 있습니다.
	// mutable 선언은 멤버 변수를 const 함수에서도 변경할 수 있도록 해줍니다.
	mutable int CallCount = 0;
	std::string mName;

};

int main()
{
	CMonster NewMonster;
	for (size_t i = 0; i < 10; i++)
	{
		// mutable이 변경됐는지 확인
		NewMonster.GetName();
	}
}