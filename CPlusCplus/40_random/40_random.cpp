// 40_random.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <ctime>
#include <iomanip>
#include <random>
#include <map>

int main()
{
	enum
	{
		c_style_rand,
		mt_rand,
	};

	switch (mt_rand)
	{
	case c_style_rand:
	{
		// c 스타일의 난수는 의사 난수를 생성한다.
		// 시드가 같을 경우, 같은 수를 반환함

		// seed: 무작위로 정한 첫번째 수

		// 현재 시간을 시드 값으로 설정한다.
		srand(static_cast<std::uint32_t>(time(NULL)));
		for (int i = 0; i < 5; i++)
		{
			printf("난수: %d \n", rand() % 100);
		}
		/* output
		난수: 71
		난수: 28
		난수: 49
		난수: 38
		난수: 73
		*/

		// c 스타일의 난수 로직의 문제점
		//		- time으로 시드값을 전해주게 되면 시드 값은 초단위로 변함 
		//			-> 난수에 민감한 프로그램에서 사용 불가
		//		- RAND_MAX로 인한 불균등한 난수 생성
		//		- 성능이 구림
		//			-> 내부에서 선형 합동 생성기 알고리즘을 사용하는데 구림

		// 그냥 가져다 버리는게 맞다.
		break;
	}
	case mt_rand:
	{
		// 메르센 트위스터 엔진을 이용한 난수 생성
		// 특징 
		//	- rand에 훨씬 무거움
		//	- 품질이 보장되어 있음
		//	- 의사 난수보다 난수를 생성하는 속도가 느림

		// random device 생성
		std::random_device rd;

		// 난수 생성 엔진 초기화
		std::mt19937 gen(rd());

		enum { uniform_int, normal };
		switch (normal)
		{
		case uniform_int:
		{
			// 분포(dsitribution) : 어떤 방식의 난수를 뽑아낼 지 알려주는 객체
			// 0 ~ 99 까지 난수열 균등 분포 정의
			std::uniform_int_distribution<int> dis(0, 99);

			for (int i = 0; i < 5; i++)
			{
				std::cout << "난수: " << dis(gen) << '\n';
			}

			break;
		}
		case normal:
		{
			// 평균 0, 표준 편차 1 분포 정의
			std::normal_distribution<double> dist(0, 1);

			// 10000개의 샘플로 정규 분포 난수 생성
			std::map<int, int> hist;
			for (int i = 0; i < 10000; i++)
			{
				++hist[static_cast<int>(std::round(dist(gen)))];
			}

			for (const std::pair<int,int>& Pair : hist)
			{
				std::cout << std::setw(2) << Pair.first << ' '
					<< std::string(Pair.second / 100, '*')
					<< "" << Pair.second << '\n';
			}

			/* output:
			-4 1
			-3 60
			-2 *****599
			-1 ************************2422
			 0 **************************************3884
			 1 ***********************2379
			 2 *****593
			 3 59
			 4 3
			*/

			break;
		}
		default:
			break;
		}

		break;
	}
	default:
		break;
	}
}