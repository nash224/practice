#include "AirlineTicket.h"

AirlineTicket::AirlineTicket()
{
	// 데이터 멤버 초기화
	mPassengetName = "Unknown Passenger";
	mNumberOfMiles = 0;
	mHasEliteSuperRewardsStatus = false;
}

AirlineTicket::~AirlineTicket()
{
	// 객체 소멸 시 해야 할 정리작업은 없음
}

/* 티켓 가격을 계산한다. */
int AirlineTicket::CalPrice() const
{
	if (true == GetHasEliteSuperRewardsStatus())
	{
		// VIP는 무료
		return 0;
	}

	// 티켓 가격에 0.1을 곱한 가격
	return static_cast<int>((int)GetNumberOfMiles() * 0.1);
}

const std::string& AirlineTicket::GetPassengerName() const
{
	return mPassengetName;
}

void AirlineTicket::SetPassengerName(const std::string& _Name)
{
	mPassengetName = _Name;
}

int AirlineTicket::GetNumberOfMiles() const
{
	return mNumberOfMiles;
}

void AirlineTicket::SetNumberOfMiles(int _Miles)
{
	mNumberOfMiles = _Miles;
}

bool AirlineTicket::GetHasEliteSuperRewardsStatus() const
{
	return mHasEliteSuperRewardsStatus;
}

void AirlineTicket::SetHasEliteSuperRewardsStatus(bool _Status)
{
	mHasEliteSuperRewardsStatus = _Status;
}
