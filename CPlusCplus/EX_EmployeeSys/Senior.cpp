#include "Senior.h"

Senior::Senior()
{

}

Senior::~Senior()
{

}

int Senior::GetPayment() const
{
	return 200 + static_cast<int>(mRank) * 50 * mYearOfService;
}
