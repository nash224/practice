#include "AirlineTicket.h"

AirlineTicket::AirlineTicket()
{
	// ������ ��� �ʱ�ȭ
	mPassengetName = "Unknown Passenger";
	mNumberOfMiles = 0;
	mHasEliteSuperRewardsStatus = false;
}

AirlineTicket::~AirlineTicket()
{
	// ��ü �Ҹ� �� �ؾ� �� �����۾��� ����
}

/* Ƽ�� ������ ����Ѵ�. */
int AirlineTicket::CalPrice() const
{
	if (true == GetHasEliteSuperRewardsStatus())
	{
		// VIP�� ����
		return 0;
	}

	// Ƽ�� ���ݿ� 0.1�� ���� ����
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
