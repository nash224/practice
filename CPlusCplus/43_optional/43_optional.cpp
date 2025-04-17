// 43_optional.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <optional>
#include <string_view>


// optional 값 생성해서 줄 수도 안줄 수도 있는 클래스
// 예를 들어, 특정 상황에 만족하지 않을 경우, 
// 디폴트 값 비용을 아낄 수 있음

// 객체가 optional 보다 클 수록 비용 절약 가능
// 문자열 이후의 부분을 반환합니다.
std::optional<std::string> GetText(std::string_view _Data, std::string_view _What)
{
	size_t Pos = _Data.find(_What);
	if (std::string::npos == Pos)
	{
		// std::nullopt는 미리 정의되어있는 optional 객체
		// std::string 인스턴스가 생성되지 않는다.
		// 반환 비용이 0
		return std::nullopt;
	}

	// optional에 객체를 넣어 반환
	// 내부에서 동적할당
	return _Data.substr(Pos).data();
}

int main()
{
	std::optional<std::string> TEXT = GetText("Hello World!", "Wo");

	// optional이 객체를 가지고 있지 않고, 
	// 값을 얻을려고 하면 std::bad_optional_access 발생
	// 내부에 bool로 변환하는 캐스팅 연산자가 포함되어 있음
	// operator bool()
	if (TEXT)
	{
		std::cout << TEXT.value() << '\n';
		// 역참조로 .value와 동일한 기능 제공
		std::cout << (*TEXT) << '\n';
	}

#if 0
	// 값이 존재하지 않음 
	std::string() == GetText("5", "3").value();
#endif // 0

#if 0
	// 일반적으로 optional은 레퍼런스를 포함할 수 없다.
	std::optional<std::string&> OptionRef;
#endif // 0

	std::string Hello = "World";
	// renference wrapper클래스로 한번 감싸면 레퍼런스 타입도 가능하다.
	// 그렇지만 굳이 이렇게 해야하는지는 모르겠다.
	// 그냥 ref 변수로 보내면 안되는걸까?
	std::optional<std::reference_wrapper<std::string>> TextRef = std::ref(Hello);

	if (true == TextRef.has_value())
	{
		// -> 연산자도 제공
		// 멤버 포인터를 다루는 방식과 인터페이스가 같다.
		std::cout << TextRef->get() << '\n';
	}
}
