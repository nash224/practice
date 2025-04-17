// 14_const&staticMethod.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 몬스터가 가지고 있는 속성, 그 속성을 기반으로 작동할 행동의 집합체를 정의합니다.
class CMonster
{
public:
	// static 메서드는 정적함수라고도 불리며, 객체가 동일한 작업을 수행하는 함수입니다. 
	// 정적함수와 멤버함수의 차이점은 정적함수에는 this 인자가 포함되어 있지 않습니다.
	// 즉, 객체에 종속된 개념이 아닌 클래스에 종속된 개념으로 정적함수에서는 멤버를 접근할 수 없습니다.

	// 현재 몬스터가 스폰된 수
	static int sSpawnedMonsterCount;
	// 몬스터를 생성합니다.
	static CMonster* CreateMonster()
	{
		++sSpawnedMonsterCount;
		// this; 애초부터 허락되지 않습니다. 비정적함수에서만 사용할 수 있다고 에러를 확인할 수 있습니다.
		CMonster* NewMonster = new CMonster("");
		// 정적함수는 클래스에 종속된 함수로, 생성된 객체 내부 멤버에 접근할 수 있습니다.
		NewMonster->mName = "MonsterA";
		return NewMonster;
	}

public:
	CMonster(const std::string& _Name)
		: mName(_Name)
	{

	}

	~CMonster() {}

public:
	// const 메서드는 멤버 함수내에서 객체의 속성을 변경하지 않겠다는 선언입니다. 
	// 비정적 멤버에 대해서 선언할 수 있습니다.
	const std::string& GetName() const
	{
		// const 함수에서 호출할 수 있는 함수는 const 메서드로 제한됩니다.
		// SetName("");
		return mName;
	}

	void SetName(const std::string& _Name)
	{
		mName = _Name;
	}

private:
	std::string mName;

};

// const 선언도 함수 프로토타입 선언에 포함됩니다.
// 따라서 구현부에서도 선언부와 동일하게 const를 붙여야 합니다.
//const std::string& CMonster::GetName()
//{
//
//}

int main()
{
    std::cout << "Hello World!\n";
}