// EX_FirstProject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "DataBase.h"
#include "Employee.h"
#include "UserInterface.h"

int main()
{
	if (false)
	{
		std::cout << " Testing The Employy Class.\n";
		Records::Employee Emp;
		Emp.SetFirstName("Kim");
		Emp.SetLastName("TaeHoon");
		Emp.SetEmployeeNumber(71);
		Emp.SetSalary(5000);
		Emp.Promote();
		Emp.Promote(50);
		Emp.Hire();
		Emp.Display();
	}

	if (false)
	{
		Records::DataBase MyDB;
		Records::Employee& Emp1 = MyDB.AddEmployee("Kim", "Taehoon");
		Emp1.Fire();
		Records::Employee& Emp2 = MyDB.AddEmployee("Mega", "yuchi");
		Emp2.SetSalary(500000);
		Records::Employee& Emp3 = MyDB.AddEmployee("Hm", "Duckbae");
		Emp3.SetSalary(700000);
		Emp3.Promote();
		std::cout << "All Employees: \n\n";
		MyDB.DisplayAll();
		std::cout << "Current Employees: \n\n";
		MyDB.DisplayCurrent();
		std::cout << "Former Employees: \n\n";
		MyDB.DisplayFormer();
	}

	if (true)
	{
		// 무한루프를 돌면서 메뉴를 출력하는 인터페이스 기능을 절차지향적으로 제공한다.

		Records::DataBase DB;
		bool bDone = false;
		while (!bDone)
		{
			EInput Selection = static_cast<EInput>(DisplayMenu());
			switch (Selection)
			{
			case EInput::Hire:
				DoHire(DB);
				break;
			case EInput::Fire:
				DoFire(DB);
				break;
			case EInput::Promote:
				DoPromote(DB);
				break;
			case EInput::DisplayAll:
				DB.DisplayAll();
				break;
			case EInput::DisplayCurrent:
				DB.DisplayCurrent();
				break;
			case EInput::DisplayFormer:
				DB.DisplayFormer();
				break;
			case EInput::Done:
				bDone = true;
				break;
			default:
				std::cerr << "Unknown command.\n";
				break;
			}
		}
	}
}