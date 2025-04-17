// 39_regex.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <regex>
#include <vector>
#include <string_view>
#include <algorithm>

// 정규 표현식: 문자열에서 패턴을 찾아서 다양한 작업을 수행할 수 있다.


int GetNumberToRand()
{
	static std::uint32_t Seed = 5;
	++Seed;
	srand(Seed);
	return rand();
}

std::string CreateFileName(std::string_view _Prefix, std::string_view _Surfix, std::string_view _ext)
{
	static std::string Result;
	Result.clear();

	std::string Mid = std::to_string(GetNumberToRand());

	Result += _Prefix;
	Result += "-";
	Result += Mid;
	Result += "-";
	Result += _Surfix;
	Result += _ext;

	return Result;
}

int main()
{
	enum
	{
		regex_match,
		regex_particial_match,
		parse_HTML,
		regex_iterator_HTML,
		replace_HTML,
	};

	switch (replace_HTML)
	{
	case regex_match:
	{
		const int SIZE = 10;
		std::vector<std::string> FileNames = std::vector<std::string>(SIZE);
		for (int i = 0; i < SIZE; i++)
		{
			FileNames[i] = CreateFileName("db", "log", ".txt");
		}

		FileNames.push_back("not-db-log.txt");

		// 정규 표현식은 문법 종류가 다양하고 
		// 각 문법에 따라 처리하는 엔진이 여러가지 존재한다.
		// 디폴트로 std::regex::ECMAScript 가 정의되어 있으며,
		// std::regex::icase는 대소문자를 구분하지 않는다.


		std::regex re("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);

		for (std::string_view fName : FileNames)
		{
			// std::regex_match, 전달한 인자가 정규 표현식 객체의 규칙에 부합하면 true 반환
			std::cout << fName << ": " << std::boolalpha << std::regex_match(fName.data(), re) << '\n';
		}

		/* output:
		db-58-log.txt: true
		db-61-log.txt: true
		db-64-log.txt: true
		db-68-log.txt: true
		db-71-log.txt: true
		db-74-log.txt: true
		db-77-log.txt: true
		db-81-log.txt: true
		db-84-log.txt: true
		db-87-log.txt: true
		not-db-log.txt: false
		*/

		break;
	}
	case regex_particial_match:
	{
		// 문자열에서 조건에 만족하는 패턴 일부분을 뽑아내는 예제

		std::vector<std::string> PhoneNumbers = 
		{
			"010-1234-5678", 
			"010-123-4567",
			"011-1234-5567", 
			"010-12345-6789",
			"123-4567-8901", 
			"010-1234-567"
		};

		// [01]{3}: 3자리이며 0과 1로 이루어져 있을 것
		// d{3,4} : 3자리 또는 4자리 
		// d{4}   : 4자리
		std::regex re("[01]{3}-\\d{3,4}-\\d{4}");

		// 정규 표현식에 부합하면 항목을 string으로 보관
		std::smatch Match;

		for (const std::string& Number : PhoneNumbers)
		{
			if (std::regex_match(Number, Match, re))
			{
				for (auto& i : Match)
				{
					std::cout << i << '\n';
				}
			}
		}

		break;
	}
	case parse_HTML:
	{
		std::string html = R"(
			<div class="social-login">
				<div class="small-comment">다음으로 로그인 </div>
					<div>
						<i class="xi-facebook-official fb-login"></i>
						<i class="xi-google-plus goog-login"></i>
					</div>
				</div>
			<div class="manual">
				<div class="small-comment">
					또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
				</div>
				<input name = "name" id = "name" placeholder = "이름">
				<input name = "password" id = "password" type = "password"
					, → placeholder = "비밀번호">
			</div>
				<div id="adding-comment" class = "sk-fading-circle">
					<div class="sk-circle1 sk-circle">a</div>
					<div class="sk-circle2 sk-circle">b</div>
					<div class="sk-circle3 sk-circle">asd</div>
					<div class="sk-circle4 sk-circle">asdfasf</div>
					<div class="sk-circle5 sk-circle">123 </div>
					<div class="sk-circle6 sk-circle">aax</div>
					<div class="sk-circle7 sk-circle">sxz</div>
				</div>
			)";

		std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
		std::smatch Match;
		// regex_search는 전체 문자열에서 조건에 부합하는 문자열을 match에 담고 
		// prefix와 suffix를 갱신시킨다.
		while (std::regex_search(html, Match, re))
		{
			std::cout << Match.str() << '\n';

			// prefix는 결과 이전의 문자열
			// suffix에는 결과 이후의 문자열이 들어가게 된다.
			// 같은 결과를 내뱉지 않도록 html 갱신
			html = Match.suffix();
		}
		/* output:
		<div class="sk-circle1 sk-circle">a</div>
		<div class="sk-circle2 sk-circle">b</div>
		<div class="sk-circle3 sk-circle">asd</div>
		<div class="sk-circle4 sk-circle">asdfasf</div>
		<div class="sk-circle6 sk-circle">aax</div>
		<div class="sk-circle7 sk-circle">sxz</div>
		*/

		break;
	}
	case regex_iterator_HTML:
	{
		std::string html = R"(
			<div class="social-login">
				<div class="small-comment">다음으로 로그인 </div>
					<div>
						<i class="xi-facebook-official fb-login"></i>
						<i class="xi-google-plus goog-login"></i>
					</div>
				</div>
			<div class="manual">
				<div class="small-comment">
					또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
				</div>
				<input name = "name" id = "name" placeholder = "이름">
				<input name = "password" id = "password" type = "password"
					, → placeholder = "비밀번호">
			</div>
				<div id="adding-comment" class = "sk-fading-circle">
					<div class="sk-circle1 sk-circle">a</div>
					<div class="sk-circle2 sk-circle">b</div>
					<div class="sk-circle3 sk-circle">asd</div>
					<div class="sk-circle4 sk-circle">asdfasf</div>
					<div class="sk-circle5 sk-circle">123 </div>
					<div class="sk-circle6 sk-circle">aax</div>
					<div class="sk-circle7 sk-circle">sxz</div>
				</div>
			)";

		std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
		std::smatch Match;

		std::sregex_iterator start = std::sregex_iterator(html.begin(), html.end(), re);
		std::sregex_iterator end = std::sregex_iterator();
		while (start != end)
		{
			std::cout << start->str() << '\n';
			// 내부에서 std::regex_search 호출하고 결과를 갱신함
			++start;
		}

		break;
	}
	case replace_HTML:
	{
		std::string html = R"(
			<div class="social-login">
				<div class="small-comment">다음으로 로그인 </div>
					<div>
						<i class="xi-facebook-official fb-login"></i>
						<i class="xi-google-plus goog-login"></i>
					</div>
				</div>
			<div class="manual">
				<div class="small-comment">
					또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
				</div>
				<input name = "name" id = "name" placeholder = "이름">
				<input name = "password" id = "password" type = "password"
					, → placeholder = "비밀번호">
			</div>
				<div id="adding-comment" class = "sk-fading-circle">
					<div class="sk-circle1 sk-circle">a</div>
					<div class="sk-circle2 sk-circle">b</div>
					<div class="sk-circle3 sk-circle">asd</div>
					<div class="sk-circle4 sk-circle">asdfasf</div>
					<div class="sk-circle5 sk-circle">123 </div>
					<div class="sk-circle6 sk-circle">aax</div>
					<div class="sk-circle7 sk-circle">sxz</div>
				</div>
			)";

		std::regex re(R"r(sk-circle(\d))r");		std::smatch Match;

		// std::regex_replace는 정규 표현식에 부합하는 문자열을 
		// 특정 문자열 규칙으로 치환하고 문자열을 반환한다.
		std::string Modified_HTML = std::regex_replace(html, re, "$1-sk-circle");
		std::cout << Modified_HTML << '\n';

		break;
	}
	default:
		break;
	}
	
}
