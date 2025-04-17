// 15_UTF_encoding.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// ANSI는 처음에 등장한 문자를 표현하는 체계로 1byte 즉, 255개의 문자를 표현할 수 있다.
// 
// UNICODE는 국가별로 나타내야할 문자를 표현하기 위해 설계된 표준이다. 
// UNCODE는 모든 문자들에 대한 고유한 값을 부여한다.
// 전세계적으로 문자를 합하면 2btye로 표현하지 못한다.
// 이때 UNICODE를 표현하는 여러가지 방식을 사용한다.
// 
// 전세계 문자를 호환이 가능하도록 문자를 표현하려면 4byte가 필요한데, UTF 인코딩 방식을 사용한다.
// UTF 종류는 UTF-8, UTF-16, UTF-32로 나뉘고 각각 최소 1~4, 2~4, 4byte로 나타낼 수 있다.
// 
// UTF-8은 WideByte 형식으로 1byte로 표현가능한 문자를 사용할 경우, 1byte로 할당해준다.
// UTF-32는 모든 문자를 4byte로 표현한다. 하지만 모든 문자를 4byte로 표현하는건 비효율적이다.


int main()
{
	// UTF-32 할당 및 길이 측정 예제
	std::u32string u32Str = U"UTF-32를 지원하는 리터럴문자열을 대입받습니다.";
	std::cout << "u32 str length: " << u32Str.size() << '\n';
	// output: u32 str length: 28 

	// UTF-8은 1~4바이트로 문자를 표현하며, ANSI코드와 하위호환성을 가진다.
	// ANSI 코드로 표현 가능한 것은 1바이트, 한글 또는 한자는 3바이트로 표현
	std::string u8Str = u8"이건 UTF-8 문자열입니다";
	// 문자 길이는 할당된 char 개수이다. 
	std::cout << "u8 str length: " << u8Str.size() << '\n';

	// 이상한 문자열이 출련된다. u8Str[1]은 '이' 를 표현하기 위해 UTF-8 인코딩의 두번째 바이트인데,
	// char 하나로는 한글을 표현할 수 없다. 즉, 이상한 문자가 반환된다.
    std::cout << u8Str[1] << u8Str[2] << "\n";
}
