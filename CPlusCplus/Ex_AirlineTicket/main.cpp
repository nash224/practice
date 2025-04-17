#pragma once
#include <iostream>
#include <memory>
#include "AirlineTicket.h"

// ����: Ŭ������ �ۼ��Ͽ� ��ü�� ������ �Ҹ��� �˾ƺ���.

int main()
{
	if (true)
	{
		AirlineTicket MyTicket; // ���� �޸𸮿� ��ü ����
		MyTicket.SetPassengerName("Kim TaeHoon");
		MyTicket.SetNumberOfMiles(700);
		const int Cost = MyTicket.CalPrice();
		std::cout << "Ticket Cost : " << Cost << std::endl;
	} // ����� �������� MyTicket ��ü�� ��ȿ���� �ʰ� ������ �޸𸮿��� �����ȴ�.

	if (true)
	{
		auto MyTicket = std::make_unique<AirlineTicket>(); // ���� �޸𸮿� ��ü ����
		MyTicket->SetPassengerName("Kim TaeHoon");
		MyTicket->SetNumberOfMiles(7000);
		MyTicket->SetHasEliteSuperRewardsStatus(true);
		const int Cost = MyTicket->CalPrice();
		std::cout << "Ticket Cost : " << Cost << std::endl;
	} // MyTicket ��ü�� �����Ҵ� ������ �Ҹ��ڿ��� �ڵ����� �����ȴ�.

	if (true)
	{
		AirlineTicket* Ptr = new AirlineTicket(); // ��ü�� �� �޸𸮿� �����Ҵ� 
		delete Ptr; // ��������� �� �޸𸮸� ��ȯ
	}
}