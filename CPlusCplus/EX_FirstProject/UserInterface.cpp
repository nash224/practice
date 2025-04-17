#include "UserInterface.h"
#include <iostream>

int DisplayMenu()
{
	int Selection = 0;
	std::cout << "\n";
	std::cout << "Employee Database" << "\n";
	std::cout << "----------------------------------------" << "\n";
	std::cout << "1) Hire a new employee" << "\n";
	std::cout << "2) Fire an employee" << "\n";
	std::cout << "3) Promote an employee" << "\n";
	std::cout << "4) List all employees" << "\n";
	std::cout << "5) List all current employees" << "\n";
	std::cout << "6) List all former employees" << "\n";
	std::cout << "0) Quit" << "\n";
	std::cout << "\n";
	std::cout << "--->";
	std::cin >> Selection;

	return Selection;
}

// ���ο� ������ �̸��� �Է¹޾� �����ͺ��̽��� �߰��Ѵ�.
// ������ �߻��ϸ� �ͼ����� �߻���Ű��, �̸� ó���Ѵ�.
void DoHire(Records::DataBase& _DB)
{
	std::string FirstName;
	std::string LastName;

	std::cout << "First Name?";
	std::cin >> FirstName;
	std::cout << "Last Name?";
	std::cin >> LastName;

	try
	{
		_DB.AddEmployee(FirstName, LastName);
	}
	catch (const std::exception& _e)
	{
		std::cerr << "Unable to add new employee: " << _e.what() << "\n";
	}
}

// �����ͺ��̽��� ������ �ִ��� �����
// �����ϴ� �����̶�� ��ü�� ���ͼ� �޼��带 �����Ѵ�.
void DoFire(Records::DataBase& _DB)
{
	int EmployeeNumber = 0;
	std::cout << "Employee number? ";
	std::cin >> EmployeeNumber;
	try
	{
		Records::Employee& FindEmp = _DB.GetEmployee(EmployeeNumber);
		FindEmp.Fire();
		std::cout << "Employee " << EmployeeNumber << " terminated.\n";
	}
	catch (const std::exception& _e)
	{
		std::cerr << "Unable to terminate employee: " << _e.what() << "\n";
	}
}

void DoPromote(Records::DataBase& _DB)
{
	int EmployeeNumber = 0;
	int RaiseAmount = 0;
	std::cout << "Employee number? ";
	std::cin >> EmployeeNumber;
	std::cout << "How much of a raise? ";
	std::cin >> RaiseAmount;
	try
	{
		Records::Employee& FindEmp = _DB.GetEmployee(EmployeeNumber);
		FindEmp.Promote(RaiseAmount);
	}
	catch (const std::exception& _e)
	{
		std::cerr << "Unable to promote employee: " << _e.what() << "\n";
	}
}

void DoDemote(Records::DataBase& _DB)
{
	int EmployeeNumber = 0;
	int DemoteAmount = 0;
	std::cout << "Employee number? ";
	std::cin >> EmployeeNumber;
	std::cout << "How much of a Demote? ";
	std::cin >> DemoteAmount;
	try
	{
		Records::Employee& FindEmp = _DB.GetEmployee(EmployeeNumber);
		FindEmp.Demote(DemoteAmount);
	}
	catch (const std::exception& _e)
	{
		std::cerr << "Unable to demote employee: " << _e.what() << "\n";
	}
}
