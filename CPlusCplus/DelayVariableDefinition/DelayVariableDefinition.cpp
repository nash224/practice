// DelayVariableDefinition.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 사용하지 않은 변수는 최대한 없애야 한다.
// 초기화 인자를 얻기 전까지 변수 정의는 늦추는게 좋다.

namespace Pass
{
	constexpr int MINIMUM_LENGTH = 7;

	// ex) 너무 일찍 변수를 초기화한 경우
	// 패스워드를 암호화하는 코드
	std::string EncrptPassword1(const std::string& _Pass)
	{
		// 객체 생성
		std::string Result;

		if (_Pass.length() < MINIMUM_LENGTH)
		{
			// throw 발생 시, 스택을 빠져나오게 됨
			// Result 객체는 무의미하게 생성되어 의미없는 비용 발생
			// 즉 초기화 시점을 사용 직전에 정의하는게 좋음
			throw std::logic_error("too short password");
		}

		// do something...

		return Result;
	}

	// 객체 생성 후, 대입
	// 패스워드를 암호화하는 코드
	std::string EncrptPassword2(const std::string& _Pass)
	{
		if (_Pass.length() < MINIMUM_LENGTH)
		{
			// throw 발생 시, 스택을 빠져나오게 됨
			// Result 객체는 무의미하게 생성되어 의미없는 비용 발생
			// 즉 초기화 시점을 사용 직전에 정의하는게 좋음
			throw std::logic_error("too short password");
		}


		// 객체 생성
		std::string Result;
		// 생성된 객체에 복사 대입 연산으로 대입 호출 오버헤드를 발생시킴
		// 비용을 절약하기 위해 _Result는 _Pass로 바로 초기화해야 함
		Result = _Pass;
		auto Encrpt_Func = [](const std::string& _Encrpty) { /*do something...*/ };
		Encrpt_Func(_Pass);

		return Result;
	}
}


int main()
{
	const int LoopCount = 10;

	// 루프 바깥쪽에 정의 
	// 비용: 생성자 1번 + 소멸자 1번 + 대입 n번
	std::string Name;

	for (int i = 0; i < LoopCount; i++)
	{
		// 루프 바깥쪽에 정의 
		// 비용: 생성자 n번 + 소멸자 n번
		std::string Name;
	}

	// 성능에 민감할 경우, 루프 바깥 쪽에 정의
	// 유지보수성을 향상시킬 경우, 루프 안 쪽에 정의

    std::cout << "Hello World!\n";
}
