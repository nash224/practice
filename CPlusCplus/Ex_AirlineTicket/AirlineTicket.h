#pragma once
#include <string>

class AirlineTicket
{
public:
	AirlineTicket();
	~AirlineTicket();

	int CalPrice() const;
	const std::string& GetPassengerName() const;
	void SetPassengerName(const std::string& _Name);
	int GetNumberOfMiles() const;
	void SetNumberOfMiles(int _Miles);
	bool GetHasEliteSuperRewardsStatus() const;
	void SetHasEliteSuperRewardsStatus(bool _Status);

protected:

private:
	std::string mPassengetName;
	int mNumberOfMiles;
	bool mHasEliteSuperRewardsStatus;

};