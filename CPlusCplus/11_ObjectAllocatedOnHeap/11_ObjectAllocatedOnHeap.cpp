// 11_ObjectAllocatedOnHeap.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CObject
{
public:
	CObject() = default;
	// 해당 객체에서는 기본 생성자를 사용하지 않습니다.
	CObject(int _size)
	{
		// 객체 내부에서 동적할당
		mResources = new int[_size];
	}

	// 객체가 삭제될 경우, 소멸자 호출
	~CObject()
	{
		if (nullptr != mResources)
		{
			// 동적할당된 배열 반환
			delete[] mResources;
		}

		mResources = nullptr;
	}

private:
	int* mResources = nullptr;
};

int main()
{
	// 정적배열의 경우, 배열의 수는 컴파일 타임에 결정되어야 합니다. 
	CObject ObjectArr[5];

	// 만약 배열의 size를 변수 형태로 넣어주게 되면, 컴파일 에러를 발생시킵니다.
	int Size = 65;
	/*CObject ObjectArr[Size];*/

	// 내 프로그램에서 객체를 얼마나 생성해야할 지 모르겠다. 할 때, 힙에 객체를 생성하면 됩니다.
	// 동적할당은 런타임 중에 내가 원하는 만큼(물론 충분한 메모리가 뒷받혀 줘야함) 객체를 힙에 할당할 수 있습니다.
	// 객체를 담는 배열을 힙에 동적할당 
	CObject* pObjectArr = new CObject[5];

	// 동적할당된 배열을 해제할 경우, delete[]로 명시적 반환해야 합니다. 
	delete[] pObjectArr;
	// 반환 직후, 댕글링 포인터 참조를 막기위해 nullptr로 초기화해 줍니다.
	pObjectArr = nullptr;
    std::cout << "Hello World!\n";
}