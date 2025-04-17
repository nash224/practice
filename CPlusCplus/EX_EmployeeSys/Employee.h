#pragma once

#include <string>
#include <iostream>
#include <map>


class Employee
{
	friend class EmployManager;
public:
	enum class Rank
	{
		DepartmentHead,
		Manager,
		AssistantManger,
		Associate,
		Staff,
		Intern,
		Max,
	};

public:
	static std::map<Rank, std::string> RankDocs;

public:
	Employee();
	Employee(const std::string& _Name, const std::string& _Position, Rank _Rank);
	Employee(const Employee& _Other) = default;

	virtual ~Employee();

	virtual void Print() const
	{
		std::cout << "=====================================" << '\n';
		std::cout << "직원명: " << mName << '\n';
		std::cout << "직급: " << mPosition << '\n';
		std::cout << "Rank: " << RankDocs[mRank] << '\n';
		std::cout << "Pay per month: " << GetPayment() << "만원" << '\n';
		std::cout << "=====================================" << "\n\n";
	}

	virtual int GetPayment() const;

protected:

	std::string mName;
	std::string mPosition;
	Rank		mRank = Rank::Intern;

};
