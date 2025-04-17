// async.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <cassert>

// std::async은 작업을 전달해주면, 알아서 스레드를 만들어준다.
// 그 외의 작동방식은 std::packaged_task 와 동일하다.


constexpr int RES_SIZE = 1000;

// _Start 부터 _End 까지 모두 더한 결과값을 반환합니다.
int Sum(const std::vector<int>& _Res, int _Start, int _End)
{
	assert(
		(_Start < RES_SIZE)
		|| (_End <= RES_SIZE));

	int Total = 0;
	for (int i = _Start; i < _End; i++)
	{
		Total += _Res[i];
	}

	return Total;
}

int SumParallel(const std::vector<int>& _Res)
{
	// async가 생성한 스레드에 작업의 반을 준다.
	// launch 옵션
	//		std::launch::async		- 스레드를 바로 생성해서 함수를 실행한다.
	//		std::launch::deferred	- get 함수를 호출하면 비동기적으로 실행한다.
	std::future<int> future
		= std::async(std::launch::async, Sum, std::ref(_Res), 0, static_cast<int>(_Res.size() / 2));

	// 메인 스레드에서 나머지 작업을 수행한다.
	int UpperHalf = Sum(_Res, RES_SIZE / 2, RES_SIZE);

	// 데이터를 전달받을 때까지 무한정 대기
	const int LowerHalf = future.get();
	return LowerHalf + UpperHalf;
}

int main()
{
	std::vector<int> Res = std::vector<int>(RES_SIZE);

	for (int i = 0; i < RES_SIZE; i++)
	{
		Res[i] = i;
	}

	std::cout << reinterpret_cast<__int64>(SumParallel) << " 작업의 결과 값: " << SumParallel(Res) << "\n";
	/* output:
	* 140695272568894 작업의 결과 값: 499500
	*/
}