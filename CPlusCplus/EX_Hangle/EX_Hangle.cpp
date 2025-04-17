// EX_Hangle.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

std::vector<std::string>& ExportCons(const std::u16string& _Str)
{
	static std::vector<std::string> Result;
	Result.clear();

	static const std::string Cons[] = { "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ"
										,"ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ","ㅎ" };

	for (char16_t c : _Str)
	{
		if (false == (0xAC00 <= c && c <= 0xD7A3))
		{
			continue;
		}

		const int Offset = c - 0xAC00;
		int Cons_Offset = Offset / 0x24C;
		Result.push_back(Cons[Cons_Offset]);
	}

	return Result;
}


int main()
{
	std::u16string Str = u"안녕하세요. Control Tower, Request go around line R3";
	std::vector<std::string>& Results = ExportCons(Str);
	for (auto& i : Results)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';
}