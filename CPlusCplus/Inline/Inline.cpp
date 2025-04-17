﻿// Inline.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


// inline 특징
// 함수처럼 보이고, 문맥검사를 받을 수 있다.(매크로보다 안전하다.)
// 인라인에 정의된 내용은 '컴파일 타임'에 본문에 삽입된다. 
//		=> 목적 코드 크기가 커진다. 자칫하면 방대해진다.
//		=> 잦은 페이징 교체, 캐쉬 적중률 하락
// 템플릿이 컴파일 컴파일 타임에 타입이 결정되는 것과 마찬가지로
// 인라인도 본문에 적용되려면 컴파일 타임에 결정되어야 한다.

// inline 함수의 이점
// 1. 함수 호출 비용 면제
// 2. 길이가 짧은 코드에 인라인 적용 시, 코드의 길이가 단축될 수 있음
// 3. 본문 코드 길이가 길 수록, 코드 최적화를 받게 됨


// 아웃라인 호출
// 일반적인 함수 호출
// 인라인 호출과는 반대적 개념

class Object
{
public:
	virtual void update()
	{

	}
};

class Person : public Object
{
	// 인라인화 적용 대상 함수
public:
	using age_type = int;

	// 명시적 inline 요청
	// 컴파일러에게 인라인화가 적용될 함수라고 요청한다.
	// 코드 길이에 따라 최적화되는 대상이면 인라인이 적용됨
	inline void SetAge(age_type)
	{

	}

	// 암시적 inline 요청
	// 컴파일러 판단에 따라 inline 적용 
	age_type GetAge() const
	{
		return age_type();
	}


	// 인라인화 대상이 되지 않는 함수
public:
	// 가상화가 적용된 함수는 인라인 대상 x
	// 이유: 프로그램 실행 이후, 호출이 결정되므로 
	//	프로그램 실행 전에 결정되는 인라인과는 맞지 않음
	void update() override
	{

	}

	// 재귀함수는 상황에 따라 코드량이 방대해질 수 있어서 
	// 인라인화 대상에서 제외
	void DFS()
	{
	}
	
	// 루프문도 재귀함수와 동일한 이유로 인라인화 대상에서 제외
	void SearchBorn()
	{
		for (int i = 0; i < 100; i++)
		{

		}
	}

	// 함수 호출 비용보다 길 경우, 본문에 붙여넣는 코드양이 많아짐
	// 캐시 적중률 하락으로 인라인화 대상에서 제외
	void TooMuchCode()
	{
		
	}

	// 주소를 얻을 수 있을 경우, 인라인 대상에서 제외
	// 인라인 함수는 함수처럼 보일 뿐이지, 
	// 함수가 없는데, 주소를 얻을 수 없으므로 인라인 대상에서 제외
	void GetableAdrress()
	{

	}

};

int main()
{
    std::cout << "Hello World!\n";
}