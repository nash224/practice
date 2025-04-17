// 44_tuple.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <tuple>
#include <map>

// tuple은 여러 객체를 보관할 때 사용
// struct로 tuple 기능을 대체 가능하지만, 
// 매번 선언하면 코드가 난잡하게 되는 문제가 있다
// tuple로 대체해서 사용하면 한정된 상황에서 사용하는 코드를 줄일 수 있다.

enum class EItemID { Heal, Mana, Strength };
using item_type = std::tuple<std::string, int, double>;

// 아이템 ID로 아이템 정보를 반환합니다.
item_type GetItem(EItemID Id = EItemID::Heal);

int main()
{
	enum
	{
		how_to_use,
		structrued_binding,
	};

	switch (structrued_binding)
	{
	case how_to_use:
	{
		// std::make_tuple<types>를 사용하여 튜플 객체 생성
		std::tuple<std::string, int, double> Tuple
			= std::make_tuple<std::string, int, double>("Hp포션", 5, 5.5);

		// tuple에 있는 객체를 사용하려면 get으로 뽑아내서 사용
		std::cout << "아이템 이름: " << std::get<0>(Tuple)
			<< " 아이템 ID: " << std::get<1>(Tuple)
			<< " 사용 쿨타임: " << std::get<2>(Tuple) << '\n';
		/* output: 아이템 이름: Hp포션 아이템 ID: 5 사용 쿨타임: 5.5 */
		break;
	}
	case structrued_binding:
	{
		// tuple에 들어있는 객체를 사용하려면, 일일이 get함수를 사용해야 한다.
		// 매우 번거로운 일이 아닐 수 없다.
		// 
		// c++17 이상부터 structured_binding 테크닉을 사용하여
		// 한꺼번에 뽑아낼 수 있는 기능이 추가되었다.

		// 파이썬 튜플 인터페이스와 비슷하다.
		auto [Name, Value, Cooldown] = GetItem(EItemID::Strength);

		std::cout << "아이템 이름: " << Name
			<< " 아이템 ID: " << Value
			<< " 사용 쿨타임: " << Cooldown << '\n';
		/* output: 아이템 이름: 힘 포션 아이템 ID: 5 사용 쿨타임: 60 */

		// structured binding테크닉은 tuple말고도 pair나 struct에서 사용 가능
		std::map<int, std::string> map;
		for (auto& [Value, Str] : map)
		{

		}

		struct FInfo
		{
			int V1 = 0;
			char V2 = 0;
			double V3 = 0;
		};

		FInfo Info;
		auto& [V1, V2, V3] = Info;

		break;
	}
	default:
		break;
	}

}

item_type GetItem(EItemID Id /*= EItemID::Heal*/)
{
	switch (Id)
	{
	case EItemID::Heal:
		return std::make_tuple("힐 포션", 5, 5.5);
	case EItemID::Mana:
		return std::make_tuple("마나 포션", 10, 5.5);
	case EItemID::Strength:
		return std::make_tuple("힘 포션", 5, 60.0);
	default:
		break;
	}

	return std::make_tuple("NULL", -1, 10000000000000.0);
}