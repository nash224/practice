// dynamic&staticBinding.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


// 정적 바인딩: 컴파일 시간에 결정
// 동적 바인딩: 런타임에 결정

// 정적 타입: 컴파일 시간에 매개변수가 결정되는 것

// virtual 함수는 동적 바인딩이 되기 마련, 기본 매개변수 값은 정적 바인딩된다.
// 기본 매개변수의 값은 물려주는 쪽에서 결정된다. 무려 파생 클래스에서 재정의 하더라도

// 문제 해결방안으로 비가상 함수 인터페이스 (NVI)-관용구를 이용하면,
// 자식에서 기본 매개변수 값을 재정의하여 제대로 반영되지 않는 문제를 해결할 수 있다.

// 비가상 함수 인터페이스(NVI) - 관용구란, 
// 기본 클래스에서 public 비가상 함수를 물려주고, 
// 함수 내부에서는 private 가상 함수를 호출한다.
// 
// 파생 클래스에서 호출할 함수는 비가상으로 인터페이스만 물려주고
// 내부 구현은 virtual 함수가 담당해서 마치 virtual함수와 같은 형태로 사용하는 것이다.

#define SOLVE_THIS_PROBLEM

enum EColor {Red, Blue, Green};
std::string ToString(EColor _Color)
{
	std::string Result;
	switch (_Color)
	{
	case Red:
		Result = "Red";
		break;
	case Blue:
		Result = "Blue";
		break;
	case Green:
		Result = "Green";
		break;
	default:
		break;
	}

	return Result;
}


// 화면에 무언가 그릴 수 있는 객체
class Shape
{
#ifdef SOLVE_THIS_PROBLEM
public:
	// 비가상 함수로 기본 매개변수 값 지정
	// 내부에서 실제로 동작할 함수에 인자를 넘겨준다.
	void Draw(EColor _Color = EColor::Red) const
	{
		DoDraw(_Color);
	}

private:
	// 모양 그리기의 실제 구현
	// 비가상 함수에서 호출되기 때문에 
	// private으로 선언하여 실제 구현의 내용만 담당한다.
	virtual void DoDraw(EColor _Color) const
	{
		std::cout << "Draw" << ToString(_Color) << " Shape\n";
	}

#else
public:
	// virtual
	virtual void Draw(EColor _Color = EColor::Red) const
	{
		std::cout << "Draw" << ToString(_Color) << " Shape\n";
	}

#endif // SOLVE_THIS_PROBLEM

};

// 화면에 사각형을 그릴 수 있음 
class Rectangle : public Shape
{
#ifdef SOLVE_THIS_PROBLEM
private:
	// 가상 함수를 재정의하여 Draw함수를 재정의한다.
	virtual void DoDraw(EColor _Color)
	{
		std::cout << "Draw" << ToString(_Color) << " Rectangle\n";
	}

#else
public:
	// 파생 클래스에서 기본 매개변수의 값을 재정의하고 있지만, 
	// 기본 매개변수의 값은 정적 타입(static type)인 특성상 반영은 안될 것이다.
	// 예기치 못하는 코드는 막아야 한다.
	virtual void Draw(EColor _Color = EColor::Green) const override
	{
		std::cout << "Draw" << ToString(_Color)<< " Rectangle\n";
	}

#endif // SOLVE_THIS_PROBLEM

};


int main()
{
	Rectangle NewRec;
	// pR의 
	// 정적 타입은 Shape*, 
	// 동적 타입은 Rectangle*
	// virtual 함수는 동적 타입의 가상 함수 테이블 포인터에서 찾는다.
	Shape* pR = &NewRec;
	pR->Draw();
#ifdef SOLVE_THIS_PROBLEM
	// DrawRed Shape
	/*DrawRed Rectangle*/

#else
	// rectangle에서 기본 매개변수 값을 green으로 재정의했지만, red가 출력
	/*DrawRed Rectangle*/

#endif // SOLVE_THIS_PROBLEM

}