// 26_promise&future.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cassert>
#include <thread>
#include <future>
#include <fstream>
#include <chrono>

// c++에서 동기적(synchronouse)이란, 순차적으로 실행되는 작업
// 비동기적(asynchronouse)이란, 프로그램이 여러 실행흐름을 갖는 것

// std::future와 std::promise는 비동기적 실행에서 
// 객체를 이용해서 스레드간에 데이터를 주고 받을 수 있도록 도와준다.

void GetStreamData(std::ifstream& _In, std::string* _pResult);

void Read(std::promise<std::string>* _pPromise, std::string _Path)
{
	assert(nullptr != _pPromise);

	std::ifstream In(_Path);
	try
	{
		if (true == In.is_open())
		{
			std::string Buffer;

			GetStreamData(In, &Buffer);

			// 데이터를 등록한다.
			_pPromise->set_value(Buffer);

			In.close();
		}
		else
		{
			throw std::runtime_error("존재하지 않는 파일을 열려고 했습니다.");
		}
	}
	catch (...)
	{
		// promise에 익셉션을 등록
		// std::current_exception은 현재 익셉션을 포인터로 반환해 준다.
		// Q: 다른 스레드에서 익셉션이 발생하면 덮어 씌워지나?
		_pPromise->set_exception(std::current_exception());
	}
}

int main()
{
	// 나중에 데이터를 돌려받겠다는 약속
	std::promise<std::string> p;

	// 나중에 데이터를 돌려주겠다는 약속
	std::future<std::string> Data = p.get_future();

	std::thread t = std::thread(Read, &p, "ATC.txt");

#if 0
	// promise가 데이터를 줄때까지 대기
	Data.wait();

#else
	// 1ms동안 기다렸다 즉시 리턴
	std::future_status Stat = Data.wait_for(std::chrono::nanoseconds(1));

	// 시간이 지났는데도 데이터를 얻지 못할 경우, timeout로 설정
	if (std::future_status::timeout == Stat)
	{
		while (true)
		{
			std::cout << "Wait...\n";

			Stat = Data.wait_for(std::chrono::nanoseconds(1));
			// 기다리는 시간이 끝났을 경우, 데이터를 받을 수 있다면 ready로 설정됨
			if (std::future_status::ready== Stat)
			{
				break;
			}
		}
	}

#endif // 0


	t.detach();

	// 받은 데이터를 전달 받는다.
	// get은 future 내부에 있는 객체가 이동하기 때문에 다시 호출 x
	try
	{
		std::cout << Data.get() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void GetStreamData(std::ifstream& _In, std::string* _pResult)
{
	assert(nullptr != _pResult);
	_In.seekg(0, std::ios_base::end);

	const size_t SIZE = _In.tellg();

	_In.seekg(0, std::ios_base::beg);

	_pResult->resize(SIZE);
	_In.read(&(*_pResult)[0], SIZE);
}
