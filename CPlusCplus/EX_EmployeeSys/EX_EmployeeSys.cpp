// EX_EmployeeSys.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Employee.h"
#include "Senior.h"
#include "EmployManager.h"

int main()
{
	EmployManager NewManager;

	NewManager.CreateEmployee<Employee>("길", "인턴", Employee::Rank::Intern);
	NewManager.CreateEmployee<Employee>("하하", "사원", Employee::Rank::Staff);
	NewManager.CreateEmployee<Employee>("노홍철", "대리", Employee::Rank::AssistantManger);
	NewManager.CreateEmployee<Senior>("박명수", "대리", Employee::Rank::Manager);
	NewManager.CreateEmployee<Senior>("유재석", "부장", Employee::Rank::DepartmentHead);

	NewManager.PrintList();

    std::cout << "Hello World!\n";
}