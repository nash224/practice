// 17_exception.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

// 참조한 배열을 출력합니다.
void OutOfRangeFunc(const std::vector<int>& _vec, int _Index)
{
	if (_vec.size() <= _Index)
	{
		// c++에서 제공하는 예외처리 객체
		// throw 발생 시, 예최처리 구문까지 점프
		// 예외처리 callstack 이후의 사용중인 메모리를 모두 정리해줌
		// 단, 소멸자를 제대로 작성했다는 가정 하에
		throw std::out_of_range("배열의 범위를 넘어선 항목을 참조하려 했습니다.");
	}
	std::cout << _vec.at(_Index) << '\n';
}

// 내부에서 동적할당이 이뤄집니다.
class Resource
{
public:
	Resource(int _Size)
	{
		std::cout << "리소스 생성" << '\n';
		mPtr = new int[_Size];
	}

	~Resource()
	{
		if (nullptr != mPtr)
		{
			std::cout << "리소스 해제" << '\n';

			delete mPtr;
			mPtr = nullptr;
		}
	}

private:
	int* mPtr = nullptr;
};

// 내부에서 동적할당하는 객체가 생성되고 의도적으로 throw를 던집니다.
void funcC()
{
	Resource Res(5);
	throw std::runtime_error("Intentional error!");
	std::cout << "FuncC 리턴" << '\n';
}

void funcB()
{
	Resource Res(5);
	funcC();
	std::cout << "FuncB 리턴" << '\n';
}

void funcA()
{
	Resource Res(5);
	funcB();
	std::cout << "FuncA 리턴" << '\n';
}

// std::exception을 상속받아 예외 처리할 수 있음
class UserException : public std::exception
{
public:
	const char* what() const noexcept override { return "Exception Occur"; };
};

void Excepttttt()
{
	throw UserException();
}

template<typename T>
void ExceptAndPassExceptionObject()
{
	throw T();
}

// noexcept는 컴파일러에게 예외처리를 하지않겠다고 알려줍니다.
// 내부에서 하는 일 없이 throw를 던집니다.
void Move(int&, int&) noexcept
{
	// throw 1;
	// 런타임 에러 발생!
}

int main()
{
	enum ExceptionTest 
	{ 
		OutOfRange, 
		OverMaxSize, 
		c_style, 
		throw_, 
		stack_unwinding, 
		exception_inheritance, 
		else_catch, 
		noexcept_declare
	};

	switch (noexcept_declare)
	{
	case OutOfRange:
	{
		std::vector<int> Vec(3);
		const int What = Vec.at(4);
		break;
	}
	case OverMaxSize:
	{
		if (false)
		{
			// 4기가 할당되는데 프로그램이 멈춰버림 이유는 모름
			std::vector<int> Vec(1000000000);
		}

		std::vector<int> Vec;
		const size_t MAX_SIZE = Vec.max_size();
		std::cout << MAX_SIZE << '\n';
		// output: 461.1686.0184.2738.7903
		// 동적할당 가능한 크기는 엄청 많음 사실 무한대라고 봐야할듯 
		// 그런데 난 못돌리겠음 이거 돌리면 내 디스크 뻑날 것 같음
		break;
	}
	case c_style:
	{
		// c 스타일은 반환값으로 예외 처리했음

		// 엄청 순식간인데?
		const int MallocSize = 1'000'000'000;
		char* c = (char*)malloc(MallocSize);
		if (NULL == c)
		{
			printf("메모리 할당 오류: ");
			return 0;
		}

		break;
	}
	case throw_:
	{
		std::vector<int> Bins = { 0, 0, 1, 0, 1, 1, 1};

		// try-catch는 throw와 함께 사용됨
		// try문은 예기치 못한 상황이 발생할 것 같은곳에서 걸어둠
		try
		{
			OutOfRangeFunc(Bins, 10);
		}
		// try이후의 스택에서 발생한 throw를 catch로 받을 수 있음
		// throw문에서 전달한 예외처리 객체를 what함수로 메세지를 들여다 볼 수 있다.
		catch (const std::exception& e)
		{
			std::cout  << e.what() << '\n';
		}
		break;
	}
	case stack_unwinding:
	{
		try
		{
			funcA();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		break;
		/* output:
		리소스 생성
		리소스 생성
		리소스 생성
		리소스 해제
		리소스 해제
		리소스 해제
		Intentional error!*/

		// throw가 발생해도 정상적으로 소멸자가 호출된다.
	}
	case exception_inheritance:
	{
		try
		{
			Excepttttt();
		}
		catch (const std::exception& e)
		{
			// expcetion의 what을 자식에서 재정의하여 객체 내부에서 정의된 메세지를 what으로 확인가능
			std::cout << e.what() << '\n';
			// output: Exception Occur
		}
	}
	case else_catch:
	{
		try
		{
			ExceptAndPassExceptionObject<float>();
		}
		// catch문은 줄줄이 작성할 수 있음
		// throw로부터 전달받은 예외 객체 타입에 따라 catch구문이 정해짐
		catch (const int& e)
		{
			
			std::cout << "catch int exception object" << e << '\n';
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		// catch 표현식에 '...'를 작성하면 나머지라는 의미로 
		// 모든 타입을 받을 수 있음
		catch (...)
		{
			std::cout << "catch의 else 구문 실행\n";
		}
	}
	case noexcept_declare:
	{
		try
		{
			int a = 5;
			int b = 6;
			Move(a,b);
		}
		catch (int& _e)
		{
			std::cout << _e;
			int a = 0;
		}
	}
	default:
		break;
	}
}