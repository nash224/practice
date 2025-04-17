// 07_fstream.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
	if (false)
	{
		std::ifstream In("test.txt");
		if (true == In.is_open())
		{
			std::string str;
			In >> str;
			std::cout << "입력받은 문자열: ";

			std::cout << str << ' ';

			// 사용이 끝난 파일 핸들 반환
			In.close();
		}
		else
		{
			std::cout << "존재하지 않는 파일을 열려고 했습니다." << '\n';
		}
	}

	if (false)
	{
		std::ifstream In("test.txt", std::ios_base::binary);

		if (true == In.is_open())
		{
			int Num = 0;
			// 내부에 작성된 데이터를 읽어들이는 함수
			// 첫번째 인자: 결과를 반환받을 포인터
			// 두번째 인자: 읽어들일 글자의 수 
			In.read(reinterpret_cast<char*>(&Num), 4);
			std::cout << std::hex << Num << '\n';
			// output: 6c6c6548
			
			// 사용이 끝난 파일 핸들 반환
			In.close();
		}
		else
		{
			std::cout << "존재하지 않는 파일을 열려고 했습니다." << '\n';
		}
	}

	if (false)
	{
		std::ifstream In("test.txt");

		if (true == In.is_open())
		{
			std::string s;

			// 현재 스티림 위치를 가리키는 커서를 맨 끝으로 이동
			In.seekg(0, std::ios_base::end);

			// 커서 위치 반환 (파일 전체 크기)
			const size_t SIZE = In.tellg();

			In.seekg(0, std::ios_base::beg);

			s.resize(SIZE);
			In.read(&s[0], SIZE);

			std::cout << s << '\n';
		}
		else
		{
			std::cout << "존재하지 않는 파일을 열려고 했습니다." << '\n';
		}
	}

	if (false)
	{
		std::ofstream out("WriteTest.txt");
		if (true == out.is_open())
		{
			// 파일이 존재하지 않을 경우, 파일 생성 후 쓰기
			// 파일이 존재할 경우, 내용물이 전부 덮어 씌워짐
			out << "발할라로 떠나는 여행";
		}
		else
		{
			std::cout << "존재하지 않는 파일을 열려고 했습니다." << '\n';
		}
	}

	if (true)
	{
		int Input;
		std::cout << "========= 문자열로 변환기능 예제 =========\n" << "변환할 int형 데이터를 입력해주세요.\n 입력: ";
		std::cin >> Input;

		std::stringstream ss;
		ss << Input;
		std::cout << ss.str() << "으로 변환하였습니다.\n";
	}
}