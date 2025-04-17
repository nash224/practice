// ClassReferenceTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

// 클래스에서 참조자 멤버변수를 이니셜라이저 시점에서 초기화할 수 있다.
// 그런데 메모리가 해제된 참조자의 데이터 멤버는 어떤 값일까?


class CPlayer
{
public:
	void DoSomething() {}

private:
	// 확인용 멤버변수 선언
	int mArr[5] = {};
};

class CBoard
{
public:
	CBoard(const CPlayer& _Player)
		: mRefPlayer(_Player)
	{

	}

	void DoSomething()
	{
		// Player의 메모리는 쓰레기 값이 들어있다. 이걸 사용하려고 접근한다면 해제된 메모리에 Access 위반이 발생한다.
		mRefPlayer;
	}

private:
	const CPlayer& mRefPlayer;

};

int main()
{
	CPlayer* NewPlayer = new CPlayer();
	// Board 생성시점의 힙에 생성한 Player 인자를 넘겨주고
	CBoard Board = CBoard(*NewPlayer);
	// 그리고 할당된 플레이어 메모리를 반환한다.
	delete NewPlayer;
	// 무슨 값을 가리키는지 디버그 모드로 확인
	Board.DoSomething();

    std::cout << "Hello World!\n";
}