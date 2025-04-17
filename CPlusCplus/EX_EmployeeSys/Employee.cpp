#include "Employee.h"

std::map<Employee::Rank, std::string> Employee::RankDocs =
{
	{Rank::DepartmentHead,  "DepartmentHead"},
	{Rank::Manager,         "Manager" },
	{Rank::AssistantManger, "AssistantManger" },
	{Rank::Associate,       "Associate" },
	{Rank::Staff,           "Staff" },
	{Rank::Intern,          "Intern" },
};

Employee::Employee()
{

}

Employee::~Employee()
{

}

Employee::Employee(const std::string& _Name, const std::string& _Position, Rank _Rank)
	: mName(_Name)
	, mPosition(_Position)
	, mRank(_Rank)
{

}

int Employee::GetPayment() const
{
	return 200 + static_cast<int>(mRank) * 50;
}
