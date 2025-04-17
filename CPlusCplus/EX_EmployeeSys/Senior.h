#pragma once
#include "Employee.h"


class Senior : public Employee
{
public:
	Senior();
	~Senior();

	int GetPayment() const override;

	void Print() const override
	{
		std::cout << "=====================================" << '\n';
		std::cout << "직원명: " << mName << '\n';
		std::cout << "직급: " << mPosition << '\n';
		std::cout << "Rank: " << RankDocs[mRank] << '\n';
		std::cout << "연차: " << mYearOfService << '\n';
		std::cout << "Pay per month: " << GetPayment() << "만원" << '\n';
		std::cout << "=====================================" << "\n\n";
	}

protected:

private:
	int mYearOfService = 1;
};