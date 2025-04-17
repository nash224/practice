// EX_Calcurator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 목적: 전문가를 위한 c++ 4장을 학습한 내용으로 간단한 소프트웨어 디자인을 구현해본다.
// 기능: 
//	1. 계산은 피연산자 2개와 연산자, 결과값으로 구성된다.
//	2. 계산과 결과값은 콘솔로 렌더링되야 한다.
//		결과값이 갱신되면 해당 결과값을 피연산자로 사용할 수 있어야 한다.
//	3. 덧셈, 뺄셈, 곱셈, 나눈셈 기능이 포함되어야 한다.
//		3-1. 나눗셈의 경우, 0으로 나누게 되면 화면에 NAN을 출력한다.
//	4. 취소 기능은 필드를 순서대로 지울 수 있어야한다.
//		4-1. 취소 기능은 backpsace로 구현할 것

#include <iostream>
#include <array>

enum class EOperator
{
	Plus = '+',
	Minus = '-',
	Mul = '*',
	Div = '/',
};

class Interpretor
{
	static size_t GetOperandLine(const std::string& _MSG)
	{
		_MSG.find(static_cast<char>(EOperator::Plus),);
	}

	static void Isvalid(const std::string& _MSG)
	{
		if (true == _MSG.empty())
		{
			// Error
			return;
		}

		for (char Char : _MSG)
		{
			switch (static_cast<EOperator>(Char))
			{
			case EOperator::Plus:
				break;
			case EOperator::Minus:
				break;
			case EOperator::Mul:
				break;
			case EOperator::Div:
				break;
			default:
				break;
			}
		}
	}
};

int main()
{
	std::string Buffer;
	bool bLoop = false;
	while (true == bLoop)
	{
		std::cin >> Buffer;
		if (true == IsValid(Buffer))
		{

		}
		;
		Calcurate();
	}
    std::cout << "Hello World!\n";
}
