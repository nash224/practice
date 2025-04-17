#include "Employee.h"
#include <iostream>

// Employee.cpp 는 메서드에 대한 구현을 담고있다.

using namespace Records;

Employee::Employee()
	:mFirstName("")
	, mLastName("")
	, mEmployeeNumber(-1)
	, mSalary(0)
	, mHired(false)
{ 
}

Employee::~Employee()
{

}

void Employee::Promote(int _RaiseAmount)
{
	SetSalary(GetSalary() + _RaiseAmount);
}

void Employee::Demote(int _DemeritAmount)
{
	SetSalary(GetSalary() - _DemeritAmount);
}

void Employee::Hire()
{
	mHired = true;
}

void Employee::Fire()
{
	mHired = false;
}

void Employee::Display() const
{
	std::cout << "========================================" << "\n";
	std::cout << "Employee: " << GetLastName() << ", " << GetFirstName() << "\n";
	std::cout << "----------------------------------------" << "\n";
	std::cout << (mHired ? "Current Employee" : "Former Employee") << "\n";
	std::cout << "Employee Number: " << GetEmployeeNumber() << "\n";
	std::cout << "Salary: $" << GetSalary() << "\n";
	std::cout << "========================================" << "\n";
	std::cout << "\n";
}

// Getter와 Setter를 이용하면 Setter 내부에서 추가 행동을 정의할 때 일관적으로 반영할 수 있으며,
// 해당 변수 이용시점에서 브래이크 포인트를 걸어 디버깅이 쉬워진다.

void Employee::SetFirstName(const std::string& _FirstName)
{
	mFirstName = _FirstName;
}

const std::string& Employee::GetFirstName() const
{
	return mFirstName;
}

void Employee::SetLastName(const std::string& _LastName)
{
	mLastName = _LastName;
}

const std::string& Employee::GetLastName() const
{
	return mLastName;
}

void Employee::SetEmployeeNumber(int _Number)
{
	mEmployeeNumber = _Number;
}

int Employee::GetEmployeeNumber() const
{
	return mEmployeeNumber;
}

void Employee::SetSalary(int _Number)
{
	mSalary = _Number;
}

int Employee::GetSalary() const
{
	return mSalary;
}

bool Employee::IsHired() const
{
	return mHired;
}
