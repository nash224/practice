#pragma once

#include <vector>
#include <string>

class Employee;

class EmployManager
{
public:
	EmployManager();
	~EmployManager();

	template <typename ObjectType, typename RankType>
	Employee* CreateEmployee(const std::string& _Name, const std::string& _Position, RankType _Rank)
	{
		ObjectType* Employees = new ObjectType();
		Employees->mName = _Name;
		Employees->mPosition = _Position;
		Employees->mRank = _Rank;
		mEmployees.push_back(Employees);
		return Employees;
	}

	inline int GetNumOfEmployee() const { return static_cast<int>(mEmployees.size()); }

	void PrintList() const;

protected:

private:
	std::vector<Employee*> mEmployees;

};