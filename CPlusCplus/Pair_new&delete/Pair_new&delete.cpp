// Pair_new&delete.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <crtdbg.h>

// new 및 delete를 사용할 경우, 형태를 맞춰야 한다.

// new를 사용하여 힙에 객체 생성할 경우, 반환되는 포인터는 단일 객체를 가리킨다.
// new[]를 사용할 경우, 반환되는 포인터는 객체의 배열에 대한 정보를 가리킨다.

// 그에 맞춰 delete는 단일 객체의 소멸자를 호출한다.
// delete[]는 배열 수만큼 객체의 소멸자를 호출한다.

struct BigData
{
	int Arr[50];
};

class Object
{
public:
	~Object()
	{
		std::cout << "Object 소멸자 호출!\n";
	}

private:
	BigData mData;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if 0
	// 경고는 발생하지만, 치명적인 오류는 발생하지 않음
	// 컴파일러마다 다르며, 엔진 자체가 무거워 졌을때 안전성을 보장할 수 없음
	Object* pObject = new Object;
	delete[] pObject;
#endif // 0

#if 0
	// 배열에 대한 정보를 찾을 수 없어서 치명적인 오류 발생
	// 절대 사용x
	Object* pObjectArr = new Object[100];
	delete pObjectArr;
#endif // 0




    std::cout << "Hello World!\n";
}
