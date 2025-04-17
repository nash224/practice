// 10_VariadicTemplate.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 가변 길이 템플릿은 여러 타입에 대한 0개 이상의 인자를 받을 때 사용한다.

// 이 함수는 Print(const T&, _Types) 함수보다 우선 순위가 높다. 즉, 먼저 실행되는데,
// 템플릿 파라미터 팩이 1개 남았을 경우, 재귀적으로 실행되다 마지막으로 호출된다.
template<typename T>
void Print(const T& _TArg)
{
	std::cout << _TArg << '\n';
}

// 가변 길이 템플릿 선언은 typename뒤에 ... 를 붙이고,
// 가변 인자를 사용할 때는 타입앞에 ... 를 붙이면 된다.
template<typename T, typename... Types>
void Print(const T& _TArg, Types... _TArgs)
{
	std::cout << _TArg<< ", ";
	// 재귀 함수 호출
	Print(_TArgs...);
}

// 가변 인자 호출 순서
template<typename T>
std::string StrCat(const T& _TArg)
{
	return _TArg;
}

// a,b,c,d 인자를 받을 경우, 재귀적으로 호출되어 std::string(a) + b + c + d로 치환되어 반환
template<typename T, typename... Strs>
std::string StrCat(const T& _TArg, Strs... _TStr)
{
	return std::string(_TArg) + StrCat(_TStr...);
}

int SumAll()
{
	return 0;
}

// 전달해준 가변 인자의 모든 수의 합을 반환합니다.
template<typename T, typename... Types>
int SumAll(const T& _Arg, Types... _Args)
{
	return _Arg + SumAll(_Args...);
}

// 전달받은 가변인자의 평균을 반환합니다.
template<typename... Types>
double Average(Types... _Args)
{
	const double SUM = static_cast<double>(SumAll(_Args...));
	const double ArgsCount = static_cast<double>(sizeof...(_Args));
	return SUM / ArgsCount;
}

// c++17 부터 지원하는 Fold 방식 재귀 호출
// 기존에 재귀함수의 마지막 함수를 만들어 줄 필요없이 함수 하나로 동일하게 동작할 수 있도록 제공한다.
template<typename... Types>
int SumArgs(Types... _Args)
{
	return (... + _Args);
}

// fold는 여러방식이 존재한다.
// 위에서 사용한 fold는 좌측 단항 fold방식이라고 한다.
// 밑의 함수에서 사용할 fold는 이항 우측 fold방식이다.
template<typename... Nums>
int DiffFrom(int Num, Nums... _Args)
{
	return (Num - ... - _Args);
}

template<typename ...Types>
void PrintAll(Types... _Args)
{
	(Print(_Args), ...);
}

int main()
{
	// 결론적으로 말하면 위 두 print함수를 호출하는데, 
	// 컴파일 시간에 아래에서 사용하는 Print 함수는 재귀적으로 생성될 것이다.
	// 함수에 전달할 인자를 넣었을 경우 함수가 생성되는 순서는 다음과 같다.
	// Print(int, double, char, const char*) << 다음 함수 호출에서 int가 빠져 버린다.
	// Print(double, char, const char*) << 이번엔 double이 빠져 버린다.
	// Print(char, const char*) << 이번엔 char이 빠져 버린다.
	// Print(const char*) << 다음 함수는 컴파일 우선위로 Print(const T&, Types...)보다 Print(const T&) 가 호출된다.
	Print(5, 0.6, '3', "Hello");
	// output: 5, 0.6, 3, Hello

	std::cout << StrCat(std::string("1"), "2", "3", "4");
	std::cout << "\n";

	const int SUM = SumAll(5,6,7,3,43,3);
	const int SUMB = SumArgs(5,6,7,3,43,3);
	const double AVERAGE = Average(5,6,7,3,43,3);
	const int DiffResult = DiffFrom(10, 1, 1, 1, 1);
	
	// 전달할 모든 인자가 출력된다.
	// Print("This")
	// Print("Function")
	// Print("Use")
	// Print("Fold")
	// Print("Base")
	PrintAll("This", "Function", "Use", "Fold", "Base");
}
