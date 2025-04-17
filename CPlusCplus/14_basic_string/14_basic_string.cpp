// 14_basic_string.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define SSO_CODE_ 0

#if SSO_CODE_
// 메모리 할당 확인
void* operator new(std::size_t count)
{
	std::cout << count << "bytes Alloc" << '\n';
	return malloc(count);
}

#endif // 0

template<typename T>
void PrintType()
{
	std::cout << "Type is " << typeid(T).name() << '\n';
}

// std의 템플릿 클래스를 상속받아 traits를 확장한다.
struct my_char_traits : public std::char_traits<char>
{
	static int GetRank(char c)
	{
		int Result = static_cast<int>(c);
		// 문자가 아스키 숫자라면 우선순위 하락
		if (!isupper(c))
		{
			const int Num = static_cast<char>('a' - 'A');
			Result -= Num;
		}

		return Result;
	}

	static bool lt(const char* _c1, const char* _c2)
	{
		return GetRank(*_c1) < GetRank(*_c2);
	}

	static int compare(const char* _c1, const char* _c2, size_t n)
	{
		while (0 != n)
		{
			--n;

			if (GetRank(*_c1) < GetRank(*_c2))
			{
				return -1;
			}
			else if (GetRank(*_c1) > GetRank(*_c2))
			{
				return 1;
			}

			++_c1;
			++_c2;
		}

		return 0;
	}
};

int main()
{
	if (false)
	{
		// string은 basic_string에 템플릿 매개변수 char을 전달한 템플릿 인스턴스화 버전이다.
		// 예를 들어, basic_string에 wchar를 전달하면 wstring이 된다.
		// 
		// basic string은 TChar, Traits ,TAllocator 템플릿 파라미터를 받는다.
		// Tchar: 문자열에 들어갈 타입
		// Traits: 문자 타입에 대한 연산 (크기 측정, 비교 연산 등)
		// TAllocator: 

		// 대 소문자 비교를 위한 문자열 생성
		std::basic_string<char, my_char_traits> s1 = "Abc";
		std::basic_string<char, my_char_traits> s2 = "abc";

		// my_char_traits를 재정의했기 때문에 대소 문자는 같은 판정
		std::cout << "s1 == s2 : " << std::boolalpha << (s1 == s2) << '\n';
		// output: s1 == s2 : true

		std::string s3 = s1.data();
		std::string s4 = s2.data();
		std::cout << "s3 == s4 : " << std::boolalpha << (s3 == s4) << '\n';
	}

	if (SSO_CODE_)
	{
#if SSO_CODE_

		// new 연산자를 재정의하여 동적할당이 얼마나 되는지 추적
		std::cout << "s1 생성 --- " << '\n';
		std::string s1 = "this is a pretty long sentence!!!";
		std::cout << "s1 크기: " << sizeof(s1) << '\n';
		/*output :	s1 생성 ---
					16bytes Alloc
					48bytes Alloc
					s1 크기 : 40*/

		std::cout << "s2 생성 --- " << '\n';
		std::string s2 = "this is short !";
		std::cout << "s2 크기: " << sizeof(s2) << '\n';
		/*output :	s2 생성 ---
					16bytes Alloc
					s1 크기 : 40*/
#endif // SSO_CODE
	}

	if (true)
	{
		// c++ 14 이후로부터 string 문자열 리터럴을 지원한다.
		// string 리터럴을 사용하기 위한 using namespace 선언
		using namespace std::string_literals;

		// const char*로 연역되던게 std::string으로 추론된다.
		auto Str = "hello, world!"s;
		PrintType<decltype(Str)>();

		auto RawString = R"(햄보카세요 \ 
이런거도 되요
	물론이지만 탭도 가능합니다.)";
		std::cout << RawString << '\n';

		auto UserContextRawString = R"MyContext(사용자 구문 Raw문자열 리터럴입니다. )"이거 이제부터 쓸 수 있음)MyContext";
		std::cout << UserContextRawString << '\n';
	}
}
