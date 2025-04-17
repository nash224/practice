// 16_string_view.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

enum { String_Refer, String_view, Const_char_P };

#define STRING_REFER_TEST 0
#define CONST_CHAR_TEST 1
#define STRING_VIEW_TEST 2

#define TEST_CODE STRING_VIEW_TEST

#if TEST_CODE == STRING_REFER_TEST

// 단순히 리터럴을 읽을 뿐인데, 하위 식에서 암묵적 동적할당 발생
bool IsContain(const std::string& _Src, const std::string& _Sent)
{
	return std::string::npos != _Src.find(_Sent);
}
#elif TEST_CODE == CONST_CHAR_TEST 

#include <cstring>

// const char*를 받게되면 내부에서 string으로 받아 사용하거나 
// 문자열 길이를 측정하는 함수에서 추가적인 연산이 발생한다.
bool IsContain(const char* _Src, const char* _Sent)
{
	const size_t STR_LEN = strlen(_Src);
	const size_t SENTENSE_LEN = strlen(_Sent);

	for (size_t i = 0; i < STR_LEN - SENTENSE_LEN; i++)
	{
		for (size_t Offset = i; Offset < SENTENSE_LEN; Offset++)
		{
			if (_Src[Offset] != _Sent[Offset])
			{
				break;
			}

			if (SENTENSE_LEN == Offset + 1)
			{
				return true;
			}
		}
	}
	return false;
}

#elif TEST_CODE == STRING_VIEW_TEST

#include <string_view>
#include <cassert>

// c++ 17이상부터 이용 가능한 문법
// string_view는 리터럴에 대한 포인터를 가져와 string 처럼 이용할 수 있다.
bool IsContain(std::string_view _Src, std::string_view _Sent)
{
	assert(false == _Src.empty() && false == _Sent.empty());
	// string과 인터페이스가 거의 동일
	return std::string_view::npos != _Src.find(_Sent);
}

#endif // TEST_CODE




// 동적할당 시, 할당 메모리 크기 출력
void* operator new(size_t _Size)
{
	std::cout << _Size << "btyes 할당" << '\n';
	return malloc(_Size);
}


int main()
{
	enum Test{ stringMemoryAllocate, SV_substr };

	switch (SV_substr)
	{
	case stringMemoryAllocate:
	{
		// 리터럴 인자 전달
		std::cout << std::boolalpha << IsContain("Advance the throttles to full power", "to") << '\n';
		break;
	}
	case SV_substr:
	{
		std::cout << " ============= substr Test =============== \n\n";
		std::cout << "== String =============" << '\n';
		std::string s = "Pitch up for a climb-pitch attitude";
		std::cout << s.substr(0,5) << "\n";

		std::cout << "== String_view =============" << '\n';
		std::string_view sv = s;
		std::cout << sv.substr(5,14) << "\n";
		
		/* output: 
		============= substr Test ===============
		== String =============
		16btyes 할당
		48btyes 할당
		16btyes 할당
		Pitch
		== String_view =============
		 up for a clim*/

		break;
	}
	default:
		break;
	}
}