#pragma once
#include <string>

class Coupon
{
public:
	Coupon();
	~Coupon();

	int CalPrice() const;

private:
	std::string mTicketName;
	int mPrice;
	bool mActive;

};