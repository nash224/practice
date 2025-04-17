#include "DataBase.h"
#include <stdexcept>

using namespace Records;

// ���� ���� ������ �ο��� ������ȣ �ʱⰪ ����.
DataBase::DataBase()
	: mNextEmployeeNumber(kFirstEmployeeNumber)
{

}

DataBase::~DataBase()
{

}

// ���� ��ü�� �����Ͽ� �̸� ����, ��ȣ���� ������ ��ȯ�Ѵ�.
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

// �Ѱ��� ���ڷ� ������ ã�´�.
// ������ ���� ������ ���, �ͼ������� ��Ʈ��������.
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

// ���� ��ȣ�� �ش��ϴ� ������ ã�´�.
// ������ ���� ������ ���, �ͼ������� ��Ʈ��������.
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
