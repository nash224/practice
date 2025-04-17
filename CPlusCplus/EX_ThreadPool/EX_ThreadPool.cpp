// EX_ThreadPool.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <functional>
#include <future>
#include "CThreadPool.h"

void work(int _Id, int _Time)
{
	printf("%d Start \n", _Id);
	std::this_thread::sleep_for(std::chrono::seconds(_Time));
	printf("%d end \n", _Id);
}

int foo(int, int);

template<class F, class... Types>
typename std::result_of<F(Types...)>::type MakeJob(F&& _Function, Types&&... Args)
{
	return std::forward<typename std::result_of<F(Types...)>::type>(_Function(Args...));
}

int main()
{
	if (true)
	{
		// std::result_of은 리턴타입을 함수의 형태로 추론할 수 있다.
 		auto Result = MakeJob(foo, 5, 3);
	}
	if (false)
	{
		const int POOL_SIZE = 16;
		CThreadPool TPool(POOL_SIZE);

		for (int i = 0; i < 10; i++)
		{
			// 캡처 리스트에 레퍼런스로 i를 주면 안된다.
			// 메인 스레드에서 사라질 지역변수를 캡처로 넘겨주는것은 위험하다.
			std::function<void()> Job = std::bind([i]() { work(i, i); });

			TPool.RegistJob(CJob(std::move(Job)));
		}

		std::this_thread::sleep_for(std::chrono::seconds(11));

		/* otuput:
		1 Start
		0 Start
		2 Start
		4 Start
		5 Start
		3 Start
		0 end
		6 Start
		7 Start
		8 Start
		9 Start
		1 end
		2 end
		3 end
		4 end
		5 end
		6 end
		7 end
		8 end
		9 end
		*/
	}
}

int foo(int, int)
{
	return 0;
}