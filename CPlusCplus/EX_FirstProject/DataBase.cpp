#include "DataBase.h"
#include <stdexcept>

using namespace Records;

// 새로 고용된 직원에 부여할 고유번호 초기값 설정.
DataBase::DataBase()
	: mNextEmployeeNumber(kFirstEmployeeNumber)
{

}

DataBase::~DataBase()
{

}

// 직원 객체를 생성하여 이름 지정, 번호지정 수행후 반환한다.
Employee& Records::DataBase::AddEmployee(const std::string& _FirstName, const std::string& _LastName)
{
	Employee NewEmployee;
	NewEmployee.SetFirstName(_FirstName);
	NewEmployee.SetLastName(_LastName);
	NewEmployee.SetEmployeeNumber(mNextEmployeeNumber++);
	NewEmployee.Hire();

	mEmployees.push_back(NewEmployee);

	return mEmployees.back();
}

// 넘겨진 인자로 직원을 찾는다.
// 고용된적 없은 직원일 경우, 익셉션으로 터트려버린다.
Employee& Records::DataBase::GetEmployee(const std::string& _FirstName, const std::string& _LastName)
{
	for (Employee& Object : mEmployees)
	{
		if (_FirstName == Object.GetFirstName()
			&& _LastName == Object.GetLastName())
		{
			return Object;
		}
	}

	throw std::runtime_error("No Employee Found.");
}

// 직원 번호에 해당하는 직원을 찾는다.
// 고용된적 없은 직원일 경우, 익셉션으로 터트려버린다.
Employee& Records::DataBase::GetEmployee(int _Number)
{
	for (Employee& Object : mEmployees)
	{
		if (_Number == Object.GetEmployeeNumber())
		{
			return Object;
		}
	}

	throw std::runtime_error("No Employee Found.");
}

void Records::DataBase::DisplayAll() const
{
	for (const Employee& Object : mEmployees)
	{
		Object.Display();
	}
}

void Records::DataBase::DisplayCurrent() const
{
	for (const Employee& Object : mEmployees)
	{
		if (true == Object.IsHired())
		{
			Object.Display();
		}
	}
}

void Records::DataBase::DisplayFormer() const
{
	for (const Employee& Object : mEmployees)
	{
		if (false == Object.IsHired())
		{
			Object.Display();
		}
	}
}
