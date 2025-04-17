// 08_CopyConstructor.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CObject
{
public:
	CObject() = default;

	// 복사 생성자
	// 같은 클래스 타입인 다른 객체를 대상으로 복사 받을 때 호출되는 생성자
	// 복사 생성자를 선언하지 않을 경우, 컴파일러가 묵시적으로 복사 생성자를 만들어 줌
	// 
	// 컴파일러가 자동으로 생성한 복사 생성자는 기본 타입으로 복사 받게 됩니다.
	// 이 경우, 객체 내 멤버 변수 중에서 동적할당 받은 변수에 대해서 별도의 처리를 해주지 않고, 
	// 그 동적할당된 메모리를 가리키는 포인터 주소값만 복사 받게 됩니다.
	// 이런 복사를 얕은 복사라고 하고 이 문제를 방지하기 위해 사용자가 복사 생성자를 정의해야 합니다.
	// 

	/*객체의 복사본을 만들어 냅니다.*/
	CObject(const CObject& _Other)
	{
		// 복사본 객체의 멤버에 접근하여 값 복사 
		mData = _Other.mData;
	}

	inline void SetData(int _Data) { mData = _Data; }
	void PrintData() const
	{
		std::cout << "MyData: " << mData << '\n';
	}

private:
	int mData = 0;


};

int main()
{
	{
		// A 객체 호출
		CObject AObject;
		// B객체를 생성할 때, A객체를 넘겨받음
		CObject BObject = CObject(AObject);
		// C 객체를 생성할 때, B 객체를 넘겨받음
		CObject CObject{ BObject };
	}

	{
		// 정의한 복사 생성자에서 따로 멤버 복사를 하지 않을 경우, 
		// 컴파일러가 대신 복사해주는 지 의문이 들었다.
		// 따라서 복사생성자 내부 코드에 mData를 대입받는 코드를 주석걸어 실험해 보았다.

		// 결론: 컴파일러는 따로 복사해주지 않는다.
		CObject AObject;
		AObject.SetData(5);
		CObject BObject{ AObject };
		BObject.PrintData();
		// otuput: MyData: 0 
	}

    std::cout << "Hello World!\n";
}