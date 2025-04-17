// 23_Thread.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// 쓰레드는 프로세스 내에서 실행되는 흐름이다.
// 컴퓨터는 cpu에서 연산을 하는데, 
// 쓰레드의 메모리를 가져와서 명령어를 기반으로 프로그램이 동작한다.
// 
// [쓰레드의 메모리 공유]
// 쓰레드는 프로세스 내부에 있기 때문에 공유 가능한 메모리에 대해 접근할 수 있다.
// 프로세스는 운영체제가 부여해준 메모리 블록이기 때문에 
// 다른 프로세스의 메모리에 접근할 수 없다. 
// 
// [컨텍스트 스위칭]
// 운영체제의 스케줄러에 의해 실행 중인 쓰레드가 교체되면, 
// 쓰레드가 가지고 있는 메모리로 교체하는 것을 의미한다
// 
// [멀티 쓰레드]
// 쓰레드를 여러개 만들어서 프로그램을 구현하는 기법이다.
// 많은 연산 작업을 수행해야 할 때, 각 쓰레드에 연산을 나눠서 작업을 부여하고 수행한다.
// 쓰레드가 많으면 무조건 시간 단축될꺼라고 생각할 수 있지만,
// 너무 많은 쓰레드는 메모리가 많이 할당되고, 
// 가용할 cpu 수가 적다면 컨텍스트 스위칭으로 인해 작업 속도가 오히려 늦어질 수도 있다.
// 컨텍스트 스위칭은 많은 비용이 든다.
// 

void funA()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "쓰레드 1 작동!\n";
	}
}

void funB()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "쓰레드 2 작동!\n";
	}
}

void funC()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "쓰레드 3 작동!\n";
	}
}

void Job(std::vector<int>::iterator _From, std::vector<int>::iterator _To, int* _pResult)
{
	int Sum = 0;
	for (decltype(_From) Iter = _From; Iter != _To; ++Iter)
	{
		Sum += (*Iter);
	}

	const std::thread::id T_ID = std::this_thread::get_id();
	
	printf("%d부터 %d까지 합한 값은 %d입니다.\n", (*_From), *(_To - 1), Sum);

	(*_pResult) = Sum;
}

void ThreadUnsafe(int& _Count);
void ThreadSafe(std::mutex& _m,int& _Count);
void DeadLock(std::mutex& _m, int& _Count);
void LockGaurd(std::mutex& _m, int& _Count);
void CrossDeadLockA(std::mutex& _m1, std::mutex& _m2, int& _Count);
void CrossDeadLockB(std::mutex& _m1, std::mutex& _m2, int& _Count);

int main()
{
	enum 
	{ 
		parallel_oper, 
		detech, 
		pass_args_to_thread, 
		concurrency_problem, 
		thread_safe_using_mutex,
		dead_lock,
		lock_guard,
		cross_deadlock
	};
	switch (cross_deadlock)
	{
	case parallel_oper:
	{
		// 객체 생성 시, 쓰레드가 만들어진다.
		// 생성된 각 쓰레드에게 함수를 인자로 전달하여 작업을 맡긴다.
		std::thread t1(funA);
		std::thread t2(funB);
		std::thread t3(funC);

		// join함수는 쓰레드가 종료되면 리턴된다.
		// join을 거는 이유는 다른 쓰레드가 실행 중인데
		// 메인메모리가 먼저 소멸하면 다른 쓰레드를 즉시 소멸시켜버린다.
		// 예기치 못한 상황으로 간주되어 에러가 발생한다.
		t1.join();
		t2.join();
		t3.join();
		break;
	}
	case detech:
	{
		std::thread t1(funA);
		std::thread t2(funB);
		std::thread t3(funC);

		// 메인 쓰레드가 소멸되면 모든 쓰레드도 소멸된다.
		// 프로그램이 종료되어도 detach된 쓰레드를 기다려주지 않음
		t1.detach();
		t2.detach();
		t3.detach();


		break;
	}
	case pass_args_to_thread:
	{
		// thread 에서 사용할 리소스 생성
		const int SIZE = 10000;
		std::vector<int> Res = std::vector<int>(SIZE);
		for (int i = 0; i < SIZE; i++)
		{
			Res[i] = i;
		}
		
		const int THREAD_SIZE = 10;
		std::vector<int> Results = std::vector<int>(THREAD_SIZE);
		std::vector<std::thread> Workers;

		// 각 쓰레드에게 작업을 맡긴다.
		const int WORKLOAD_PER_WORKER = SIZE / THREAD_SIZE;
		for (int i = 0; i < THREAD_SIZE; i++)
		{
			Workers.push_back(std::thread(
				Job,
				Res.begin() + i * WORKLOAD_PER_WORKER, 
				Res.begin() + (i + 1) * WORKLOAD_PER_WORKER, 
				&Results[i]));
		}

		// wait for finishing job
		for (std::thread& i : Workers)
		{
			i.join();
		}

		// sum all results
		int Sum = 0;
		for (int i : Results)
		{
			Sum += i;
		}

		// print result
		std::cout << "0부터 " << SIZE << "까지 합친 값은 " << Sum << "입니다." << '\n';
		/** output: 0부터 10000까지 합친 값은 49995000입니다. */
		break;
	}
	case concurrency_problem:
	{
		// 공유 메모리 
		int Count = 0;

		const int NUM_OF_WORKER = 4;
		std::vector<std::thread> Workers;

		// 공유 메모리를 레퍼런스 형태로 넘겨버린다.
		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(ThreadUnsafe, std::ref(Count)));
		}

		for (std::thread& Worker : Workers)
		{
			Worker.join();
		}

		// 운이 좋으면 예상했던 값이 출력된다.
		// 확인해보면 실행마다 결과값이 달라질 수 있다.
		// == '디버깅이 겁나 어려워진다.'
		std::cout << "Count: " << Count << '\n';

		break;
	}
	case thread_safe_using_mutex:
	{
		// 공유 메모리 
		int Count = 0;

		const int NUM_OF_WORKER = 4;
		std::vector<std::thread> Workers;
		std::mutex m;

		// 공유 메모리를 레퍼런스 형태로 넘겨버린다.
		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(ThreadSafe, std::ref(m), std::ref(Count)));
		}

		for (std::thread& Worker : Workers)
		{
			Worker.join();
		}

		// 항상 같은 값이 나온다.
		std::cout << "Count: " << Count << '\n';

		break;
	}
	case dead_lock:
	{
		// 공유 메모리 
		int Count = 0;

		const int NUM_OF_WORKER = 4;
		std::vector<std::thread> Workers;
		std::mutex m;

		// 공유 메모리를 레퍼런스 형태로 넘겨버린다.
		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(DeadLock, std::ref(m), std::ref(Count)));
		}

		for (std::thread& Worker : Workers)
		{
			Worker.join();
		}

		// 항상 같은 값이 나온다.
		std::cout << "Count: " << Count << '\n';

		break;
	}
	case lock_guard:
	{
		// 공유 메모리 
		int Count = 0;

		const int NUM_OF_WORKER = 4;
		std::vector<std::thread> Workers;
		std::mutex m;

		// 공유 메모리를 레퍼런스 형태로 넘겨버린다.
		for (int i = 0; i < NUM_OF_WORKER; i++)
		{
			Workers.push_back(std::thread(LockGaurd, std::ref(m), std::ref(Count)));
		}

		for (std::thread& Worker : Workers)
		{
			Worker.join();
		}

		// 항상 같은 값이 나온다.
		std::cout << "Count: " << Count << '\n';

		break;
	}
	case cross_deadlock:
	{
		// 공유 메모리 
		int Count = 0;

		const int NUM_OF_WORKER = 2;
		std::vector<std::thread> Workers;
		std::mutex m1;
		std::mutex m2;

		// 공유 메모리를 레퍼런스 형태로 넘겨버린다.
		Workers.push_back(std::thread(CrossDeadLockA, std::ref(m1), std::ref(m2), std::ref(Count)));
		Workers.push_back(std::thread(CrossDeadLockB, std::ref(m1), std::ref(m2), std::ref(Count)));

		for (std::thread& Worker : Workers)
		{
			Worker.join();
		}

		// 항상 같은 값이 나온다.
		std::cout << "Count: " << Count << '\n';

		break;
	}
	default:
		break;
	}

	std::cout << "프로세스 종료\n";
}

// 공유 메모리에 대한 작업을 수행한다.
void ThreadUnsafe(int& _Count)
{
	// 10000번 더하기 연산
	for (int i = 0; i < 100000; i++)
	{
		// 한 줄 코드가 아니다. 어셈블리어 코드로 보면 5줄이 넘는 명령어로 구성되어있다.
		// cpu는 명령어 한줄을 처리한다.

		// 여러 쓰레드가 이 코드를 실행할 때, 
		// 값을 반영되기 전에 다른 쓰레드가 실행되면 이전의 결과값을 덮어 씌울 수도 있다.
		// 공유 자원에 접근할 경우, 동시성을 제어할 필요가 있다.
		_Count += 1;
	}
}

// 공유 메모리에 대한 작업을 수행한다.
void ThreadSafe(std::mutex& _m, int& _Count)
{
	// 해당 코드는 공유 자원에 대한 접근 제한을 걸어 문제가 없는 것 처럼 보이지만,
	// 뮤택스를 자주 사용하고 있다. 
	// 쓰레드가 대기하면 다른 쓰레드에게 우선순위를 넘겨줘서 컨텍스트 스위칭이 발생할 수 있는데
	// 컨텍스트 스위칭 자체가 많은 비용이 발생한다.
	// 
	// 10000번 더하기 연산
	for (int i = 0; i < 100000; i++)
	{
		// 나만 뮤텍스의 권한을 갖도록 문을 잠군다.
		// 뮤택스가 unlock될때까지 무한정 대기
		_m.lock();
		_Count += 1;
		// lock을 해제한다.
		_m.unlock();
	}

}

void DeadLock(std::mutex& _m, int& _Count)
{
	// 10000번 더하기 연산
	for (int i = 0; i < 100000; i++)
	{
		// 나만 뮤텍스의 권한을 갖도록 문을 잠군다.
		// 뮤택스가 unlock될때까지 무한정 대기
		_m.lock();
		_Count += 1;
		// 뮤텍스를 반환하지 않고 스택을 빠져나가게 되면 
		// 자신을 포함한 다른 쓰레드는 무한정 대기하는 상황이 발생한다.
		// 이를 DeadLock이라고 한다.
		// _m.unlock();

		// 컴파일러에 따라서 데드락을 처리하는 방식이 다를 수 있다.
	}
}

void LockGaurd(std::mutex& _m, int& _Count)
{
	// 10000번 더하기 연산
	for (int i = 0; i < 100000; i++)
	{
		// 뮤텍스 자원을 객체로 감싸서 관리한다.
		std::lock_guard<std::mutex> Lock(_m);
		_Count += 1;
	} // 스택을 빠져나가게 되면 소멸자에서 뮤텍스를 반환한다.
}

// A함수에서 뮤텍스1, 2 순서로 잠금을 건다.
void CrossDeadLockA(std::mutex& _m1, std::mutex& _m2, int& _Count)
{
	for (int i = 0; i < 100000; i++)
	{
		// 뮤텍스 m1을 잠그고 뮤텍스 m2를 잠근다
		// 다른쪽에서 m2를 잠그면 뮤텍스 m1에서 무한정 대기한다.
		std::lock_guard<std::mutex> Lock1(_m1);
		std::lock_guard<std::mutex> Lock2(_m2);
	}
}

// B함수에서는 A함수의 역순으로 뮤텍스를 건다.
void CrossDeadLockB(std::mutex& _m1, std::mutex& _m2, int& _Count)
{
	for (int i = 0; i < 100000; i++)
	{
		// 뮤텍스 m2을 잠그고 뮤텍스 m1를 잠근다
		// 다른쪽에서 m1를 잠그면 뮤텍스 m2에서 무한정 대기한다.
		// 만약 뮤텍스 2를 잠궜는데, 다른쪽에서 뮤텍스 1을 잠그고 뮤텍스 m2에서 대기 중이라면,
		// 해당되는 쓰레드는 무한정 대기 상태가 발생한다.
		// 결과적으로 쓰레드에서 데드락 발생
		std::lock_guard<std::mutex> Lock2(_m2);
		std::lock_guard<std::mutex> Lock1(_m1);
	}
}

