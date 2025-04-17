// 06_ios.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

int main()
{
	if (false)
	{
		while (true)
		{
			// istream은 공백, 엔터, 탭과 같은 입력을 무시한다.
			std::string Buffer;
			std::cin >> Buffer;
			std::cout << Buffer << '\n';
		}
	}

	if (false)
	{
		int Input = 0;
		while (true)
		{
			// std::hex == std::cin.setf(std::ios_base::hex, std::ios_base::basefield);
			// std::cin >> std::hex >> Input;

			// 기존 입력 받는 형식을 hex 진수로 받고 10진수로 표현
			std::cin.setf(std::ios_base::hex, std::ios_base::basefield);

			// 입력을 잘못받을 경우, istream은 fail 상태를 유지하며 그대로 반환한다.
			// 이 경우 fail 비트에 대한 처리를 해줘야 한다.
			std::cin >> Input;

			// istream 상태가 bad거나 fail일 경우, true 반환
			if (true == std::cin.fail())
			{
				std::cout << "잘못된 입력을 감지하였습니다." << '\n';
				// 플래그 초기화
				std::cin.clear();
				// 버퍼를 비운다.
				std::cin.ignore(10, '\n');
				continue;
			}

			std::cout << Input << '\n';
		}
	}

	if (true)
	{
		std::string s;
		std::cin >> s;

		// istream buffer를 가져오고 커서를 한 단어 다음의 시작부분으로 옮긴다.
		char Peek = std::cin.rdbuf()->snextc();
		if (false == std::cin.fail())
		{
			std::cout << "두 번째 맨 앞글자: " << Peek << '\n';
			std::cin >> s;
			std::cout << s << '\n';
		}
	}
}