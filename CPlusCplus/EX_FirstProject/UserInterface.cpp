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

// 새로운 직원의 이름을 입력받아 데이터베이스에 추가한다.
// 에러가 발생하면 익셉션을 발생시키고, 이를 처리한다.
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

// 데이터베이스에 직원이 있는지 물어보고
// 존재하는 직원이라면 객체를 얻어와서 메서드를 수행한다.
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
