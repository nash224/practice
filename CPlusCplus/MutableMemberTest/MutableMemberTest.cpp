// MutableMemberTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CSocket
{
public:

	__int64 Address;
};

class CServer
{
public:
	/* 소켓을 반환합니다. */
	inline CSocket* GetSocket() const
	{
		++AccessCount;
		return Socket;
	}

	// mutable 변수 사용가능 여부
	inline int GetAccessCount() const { return AccessCount; }

private:
	CSocket* Socket =nullptr;
	// mutable 선언 : const 메서드에서도 값을 변경할 수 있는 변수를 선언하겠다.
	mutable int AccessCount = 0;
};

int main()
{

	CServer Server;
	for (int i = 0; i < 100; i++)
	{
		Server.GetSocket();
	}
	std::cout << "AccessCount : " << Server.GetAccessCount() << '\n';;
}
