#include "EmployManager.h"

#include "Employee.h"

EmployManager::EmployManager()
{

}

EmployManager::~EmployManager()
{
	for (Employee* e : mEmployees)
	{
		if (nullptr != e)
		{
			delete e;
			e = nullptr;
		}
	}
}

void EmployManager::PrintList() const
{
	for (const Employee* const e : mEmployees)
	{
		if (nullptr != e)
		{
			e->Print();
		}
	}
}
