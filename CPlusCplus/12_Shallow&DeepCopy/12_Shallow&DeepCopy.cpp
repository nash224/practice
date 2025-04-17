// 12_Shallow&DeepCopy.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 동적할당된 메모리를 객체가 가지게 될 경우,
// 복사생성자, 대입연산자, 소멸자를 만들어줘야 합니다.

// 복사생성자와 대입연산자를 사용자가 만들어주지 않게 될 경우, 
// 컴파일러가 대신 만들어주는데, 컴파일러에 의해 생성된 대입연산자, 
// 복사생성자는 단순 값 복사인 얕은복사가(Shallow copy) 일어나게 됩니다.
// 
// 소멸자에선 빌린 메모리를 반환하도록 보증해야 합니다.

class CObject
{
public:
	CObject() {}
	CObject(int _size)
	{
		// 동적할당 했으면, 바로 리소스를 정리해줘야 합니다.
		Allocate(_size);
	}

	/*객체를 복사할 경우, 호출됩니다.*/
	CObject(const CObject& _Other)
	{
		std::cout << "Call Copy Constructor" << '\n';
		DeepCopy(_Other);
	}

	CObject& operator=(const CObject& _Other)
	{
		std::cout << "Call operator Equal" << '\n';
		Release();
		DeepCopy(_Other);
	}

	~CObject()
	{
		Release();
	}

public:
	CObject* At(int _Num)
	{
		if (mSize <= _Num || _Num < 0)
		{
			return nullptr;
		}
		return &pChild[_Num];
	}

private:
	void Allocate(int _size)
	{
		CObject* pChild = new CObject[_size];
		mSize = _size;
	}

	void Release()
	{
		if (nullptr != pChild)
		{
			delete[] pChild;
		}

		pChild = nullptr;
		mSize = 0;
	}

	void DeepCopy(const CObject& _Other)
	{
		Allocate(_Other.mSize);
		mSize = _Other.mSize;
		for (int i = 0; i < mSize; i++)
		{
			pChild = _Other.pChild;
		}
	}


private:
	CObject* pChild = nullptr;
	int mSize = 0;

};

int main()
{

    std::cout << "Hello World!\n";
}