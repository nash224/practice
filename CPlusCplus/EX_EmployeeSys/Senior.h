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
		std::cout << "������: " << mName << '\n';
		std::cout << "����: " << mPosition << '\n';
		std::cout << "Rank: " << RankDocs[mRank] << '\n';
		std::cout << "����: " << mYearOfService << '\n';
		std::cout << "Pay per month: " << GetPayment() << "����" << '\n';
		std::cout << "=====================================" << "\n\n";
	}

protected:

private:
	int mYearOfService = 1;
};