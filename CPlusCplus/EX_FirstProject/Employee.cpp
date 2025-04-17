#include "Employee.h"
#include <iostream>

// Employee.cpp �� �޼��忡 ���� ������ ����ִ�.

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

// Getter�� Setter�� �̿��ϸ� Setter ���ο��� �߰� �ൿ�� ������ �� �ϰ������� �ݿ��� �� ������,
// �ش� ���� �̿�������� �귡��ũ ����Ʈ�� �ɾ� ������� ��������.

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
