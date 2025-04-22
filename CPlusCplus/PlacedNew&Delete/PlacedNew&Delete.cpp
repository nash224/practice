// PlacedNew&Delete.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

bool AllocCheck(void* _ptr)
{
	return _ptr;
}

class Widget
{
public:
	// 추가 매개변수를 받는 operator new를 위치지정 new라고 함
	// 위젯을 widget 위치지정 new로 호출하는 도중에 예외가 발생할 시,
	// 메모리 누수를 막기위해 런타임 시스템이 위치지정 delete를 호출한다.
	// 
	// 위치지정 delete가 존재하지 않을 경우, '런타임 시스템은 delete를 호출하지 않는다.'
	// 
	// 예외가 발생하지 않을 경우, 위치지정 delete를 호출하지 않고,
	// 기본형태의 delete를 호출한다. 
	// 
	// 따라서 위치지정 new를 정의했다면, 예외가 발생할 상황까지 고려하여
	// 위치지정 delete와 기본형태 delete를 정의해야 한다.
	// 
	// 주의해야할 점
	//	- new를 오버로딩하는 형태로 표준 new를 가려버림 
	// 호출구문에서 표준 new형태로 사용할 경우, 컴파일 에러 발생
	static void* operator new(size_t _size, std::ostream& _logStream)
		throw(std::bad_alloc);

	// 기본형태 delete
	static void operator delete(void* _pMemory)
		throw();

	// 위치지정 delete, new와 같은 형태로 쌍을 이뤄야 한다.
	static void operator delete(void* _pMemory, std::ostream& _logStream) 
		throw();

};

int main()
{
    std::cout << "Hello World!\n";
}


void* Widget::operator new(size_t _size, std::ostream& _logStream)
throw(std::bad_alloc)
{
	// 0바이트 할당 방지
	if (0 == _size)
	{
		_size = 1;
	}

	// 파생 클래스에서 widget 클래스의 new를 호출했을 경우,
	// 전역 new에서 처리되도록 한다.
	if (sizeof(Widget) != _size)
	{
		// 전역 스코프의 new를 호출하도록 지정
		return ::operator new(_size);
	}

	// Loop문에서 할당에 대한 처리를 무조건 실행하도록 구현
	while (true)
	{
		// 메모리 할당
		void* Ptr = malloc(_size);

		// 메모리 할당에 성공했으면 반환
		if (AllocCheck(Ptr))
		{
			return Ptr;
		}

		std::new_handler g_Handler = std::set_new_handler(0);
		std::set_new_handler(g_Handler);

		// 전역 헨들러가 있으면 메모리에 대한 처리 수행
		if (nullptr != g_Handler)
		{

		}
		// 할당하지 못할 상황이라면 로그에 기록하고 throw
		else
		{
			_logStream << "Failed Alloc: ";
			throw std::bad_alloc();
		}
	}
}


void Widget::operator delete(void* _pMemory) throw()
{
	// nullptr일 경우 리턴
	if (nullptr == _pMemory)
	{
		return;
	}

	// free를 해줘야할 지는 모릅니다.
	// 단순히 의사코드를 표현하기 위해 작성함을 알려드립니다.
	free(_pMemory);
}

void Widget::operator delete(
	void* _pMemory, 
	std::ostream& _logStream
	) throw()
{
	// 기록하고
	_logStream << "Delete";

	// nullptr일 경우 리턴
	if (nullptr == _pMemory)
	{
		return;
	}

	// free를 해줘야할 지는 모릅니다.
	// 단순히 의사코드를 표현하기 위해 작성함을 알려드립니다.
	free(_pMemory);
}
