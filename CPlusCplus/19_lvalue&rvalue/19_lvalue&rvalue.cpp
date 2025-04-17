// 19_lvalue&rvalue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 좌측값(lvalue): 주소를 얻을 수 있는 값
// 표현식의 왼쪽, 오른쪽에 올 수 있음

// 우측값(rvalue): 주소를 얻어올 수 없는 값
// 므조건 표현식의 오른쪽에만 올 수 있음
// 우측값은 상수, 임시객체 등

// 인자로 전달받은 좌측값을 반환
int& Get(int& _Value) { return _Value; }
// 전달받은 인자를 값형태로 반환 << 리턴 시, 임시객체 생성
int GetConstNum(int _Value) { return _Value; }

void print(const std::string& _STr)
{
	std::cout << _STr << '\n';
}

#include <vector>

// 임시객체를 인자로 전달하려면 우측값 래퍼런스로 받으면 가능
// 함수 내부에서 _Where은 좌측값으로 사용됨
void Erase(std::vector<int>& _Vec, std::vector<int>::iterator&& _Where)
{
	_Vec.erase(_Where);
}

int main()
{
	// 좌측값 생성
	int a = 5;

	// a의 래퍼런스
	// 좌측값의 래퍼런스 가능
	int& a_l = a;

	// 5는 실제가 없는 값으로 주소를 얻어올 수 없음
	// 우측값의 래퍼런스는 불가능
#if 0
	int& a_r = 5;
#endif // 0
	// 반환값이 좌측값이면 함수는 왼쪽에 올 수 있음
	Get(a) = 100;

	// 임시객체를 반환하는 우측값은 왼쪽에 올 수 없음
#if 0
	GetConstNum(5) = 100;
#endif // 0

	// 값을 수정하지 않고 참조만 한다면 우측값도 래퍼런스로 받을 수 있음 
	const int& a_cl = 100;

	
	// 우측값의 래퍼런스
	int&& rv_r = 5;
	
	// 우측값의 래퍼런스는 우측값만 가능 
#if 0
	int&& rv_l = a;
#endif // 0

	// operator+의 반환값은 임시객체를 반환함
	// 우측값을 우측값 래퍼런스로 받게되면 임시객체는 생명시간이 연장됨
	std::string&& Temp = std::string("Hello ") + "World!";
	print(Temp);

	std::vector<int> Vec = { 0,3,4,2};
	Erase(Vec, Vec.begin());
	for (auto& i : Vec)
	{
		std::cout << i << ' ';
	}

	std::cout << '\n';
}