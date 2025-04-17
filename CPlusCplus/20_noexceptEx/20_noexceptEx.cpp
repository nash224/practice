// 20_noexceptEx.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

class Pointer
{
public:
	Pointer(int _Value = 0)
	{
		std::cout << "일반 생성자 호출" << '\n';
		mPtr = new int(_Value);
	}

	// 복사 생성자
	Pointer(const Pointer& _Other)
	{
		std::cout << "복사 생성자 호출" << '\n';
		mPtr = new int(*_Other.mPtr);
	}

	// 이동 생성자
	Pointer(Pointer&& _Other) noexcept
	{
		std::cout << "이동 생성자 호출" << '\n';
		mPtr = _Other.mPtr;
		// 전달해줄 임시객체가 포인터를 해제하지 않도록 nullptr 대입
		_Other.mPtr = nullptr;
	}

	// 복사 대입 생성자
	Pointer& operator=(const Pointer& _Other)
	{
		std::cout << "복사 대입 생성자 호출 " << '\n';
		mPtr = new int(*_Other.mPtr);
		return *this;
	}

	// 이동 대입 연산자
	Pointer& operator=(Pointer&& _Other) noexcept
	{
		std::cout << "이동 대입 생성자 호출 " << '\n';
		mPtr = _Other.mPtr;
		_Other.mPtr = nullptr;
		return *this;
	}

	~Pointer()
	{
		if (nullptr != mPtr)
		{
			delete mPtr;
			mPtr = nullptr;
		}
	}

private:
	int* mPtr = nullptr;
};


class A { public:  A(int _Value = 0) :mValue(_Value) {}; int mValue = 0; };

void g(A& _a) {std::cout << "좌측값 래퍼런스 호출\n";}
void g(const A& _a) {std::cout << "상수 좌측값 래퍼런스 호출\n";}
void g(A&& _a) {std::cout << "우측값 래퍼런스 호출\n";}

template<typename T>
void Wrapper(T& _Value)
{
	g(_Value);
}

template<typename T>
void PerfectForward(T&& _Value)
{
	g(std::forward<T>(_Value));
}

template<typename T>
void MySwap(T& _A, T& _B)
{
	// std::move로 lvalue에서 rvalue로 타입 변환하고
	// 우측값 래퍼런스를 인자로 받는 이동 대입연산자를 호출해서 swap진행
	T Temp{ std::move(_A) };
	_A = std::move(_B);
	_B = std::move(Temp);
}

int main()
{

	enum 
	{ 
		move_constructor, 
		typecast_from_l_to_r, 
		move_sentics, 
		deduce_type, 
		universal_reference,
		perfect_forward
	};
	switch (perfect_forward)
	{
	case move_constructor:
	{
		// 일반생성자 
		Pointer ptr = Pointer(5);
		// 복사생성자 호출
		Pointer PtrB = ptr;

		// 일반 생성자호출
		// 임시객체를 복사생성자의 인자로 전달하고 있음. 
		// 컴파일러 입장에서는 아무런 의미없이 연산비용을 증가시키는 로직으로 복사 생략
		Pointer PtrC(Pointer(5));

		std::cout << "=========이동연산자 noexcept 실험===========\n";
		std::vector<Pointer> Vec;
		Vec.resize(0);
		std::cout << "======첫번째 원소 추가======\n";
		Vec.push_back(ptr);
		std::cout << "======두번째 원소 추가======\n";
		Vec.push_back(ptr);
		std::cout << "======세번째 원소 추가======\n";
		Vec.push_back(ptr);

		/*
		output:
		=========이동연산자 noexcept 실험===========
		======첫번째 원소 추가======
		복사 생성자 호출
		======두번째 원소 추가======
		복사 생성자 호출
		이동 생성자 호출
		======세번째 원소 추가======
		복사 생성자 호출
		이동 생성자 호출
		이동 생성자 호출
		*/

		// 내부에서 재할당이 일어나는데, 
		// 기존에 있던 항목에 대해서는 복사할 필요는 없으므로 이동만 수행
		break;
	}
	case typecast_from_l_to_r:
	{
		// 일반생성자 호출
		Pointer A = Pointer(5);
		// 복사생성자 호출
		Pointer B = A;

		// move semantics
		// lvalue를 rvalue로 타입 변환해주는 함수
		// 결과적으로 이동 생성자 호출
		Pointer C = std::move(A);
		break;
	}
	case move_sentics:
	{
		Pointer A = Pointer(5);
		Pointer B = Pointer(3);
		MySwap(A, B);

		/* output:
		일반 생성자 호출
		일반 생성자 호출
		이동 생성자 호출
		이동 대입 생성자 호출
		이동 대입 생성자 호출
		*/
		break;
	}
	case deduce_type:
	{
		A a;
		const A ca = 5;

		std::cout << "원본 호출 ================\n";
		g(a);
		g(ca);
		g(A(3));

		std::cout << "템플릿 래퍼 호출================\n";
		Wrapper(a);
		Wrapper(ca);
#if 0
		// 좌측값 래퍼런스는 우측값을 받을 수 없음
		Wrapper(A(5));
#endif // 0

		break;
		/* output:
		원본 호출 ================
		좌측값 래퍼런스 호출
		상수 좌측값 래퍼런스 호출
		우측값 래퍼런스 호출
		템플릿 래퍼 호출================
		좌측값 래퍼런스 호출
		좌측값 래퍼런스 호출
		좌측값 래퍼런스 호출
		*/

		// 템플릿에 전달한 인자는 const나 우측값 래퍼런스를 무시해버림
		// 따라서 템플릿 인자를 받는 함수도 여러 버전을 받을 수 있도록 오버로딩을 수행해야됨
	}
	case universal_reference:
	{
		// 래퍼런스 겹침 규칙
		// 래퍼런스가 결쳐져서 타입의 형태가 결정되는 경우
		int a = 0;
		typedef int& T;
		T& TRef = a;
#if 0
		// 불가능
		// 좌측값 래퍼런스
		T& TRef = 5;
#endif // 0

		T&& TRefRef = a;

#if 0
		// 좌측값 래퍼런스
		T&& RefRef = 5;
#endif // 0

		typedef int&& U;
		U& URef = a;
#if 0
		// 불가능
		// 좌측값 래퍼런스
		U& URef = 5;
#endif // 0

		// 가능 
		U&& URefRef = 5;
#if 0
		// 불가능
		// 우측값 래퍼런스
		U&& URefRef = a;
#endif // 0


		break;
	}
	case perfect_forward:
	{
		A a;
		const A ca = 5;

		std::cout << "원본 호출 ================\n";
		g(a);
		g(ca);
		g(A(3));

		std::cout << "템플릿 래퍼 호출================\n";
		PerfectForward(a);
		PerfectForward(ca);
		PerfectForward(A(5));

		/* output
		원본 호출 ================
		좌측값 래퍼런스 호출
		상수 좌측값 래퍼런스 호출
		우측값 래퍼런스 호출
		템플릿 래퍼 호출================
		좌측값 래퍼런스 호출
		상수 좌측값 래퍼런스 호출
		우측값 래퍼런스 호출
		*/

		break;
	}
	default:
		break;
	}
}