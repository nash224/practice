// 28_pakaged_task.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <thread>
#include <future>

int DoSomething(int _Num)
{
	int Sum = 0;
	for (int i = 0; i < _Num; i++)
	{
		Sum += i;
	}
	return Sum;
}

// std::packaged_task는 스레드에 함수을 넘겨주고, 
// 스레드가 실행한 함수의 리턴값을 future가 받는 기능을 제공한다.
int main()
{
	// std::packaged_task는 실행할 함수를 받아서 작업을 수행하면, future에 값을 넣어준다.
	std::packaged_task<int(int)> Task(DoSomething);
	// 함수의 반환값을 템플릿 인자로 리턴 타입을 명시해야 한다.
	std::future<int> Data = Task.get_future();

	// packaged_task은 우측값을 인자로 받는다.
	std::thread t(std::move(Task), 100);

	// 데이터가 들어올때까지 무한정 대기
	std::cout << reinterpret_cast<__int64>(DoSomething) << "을 실행한 결과: " << Data.get() << '\n';
	t.join();
}