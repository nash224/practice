#pragma once
#include <iostream>
#include <memory>
#include "AirlineTicket.h"

// 목적: 클래스를 작성하여 객체의 생성과 소멸을 알아본다.

int main()
{
	if (true)
	{
		AirlineTicket MyTicket; // 스택 메모리에 객체 생성
		MyTicket.SetPassengerName("Kim TaeHoon");
		MyTicket.SetNumberOfMiles(700);
		const int Cost = MyTicket.CalPrice();
		std::cout << "Ticket Cost : " << Cost << std::endl;
	} // 블록을 빠져나면 MyTicket 객체는 유효하지 않게 됨으로 메모리에서 정리된다.

	if (true)
	{
		auto MyTicket = std::make_unique<AirlineTicket>(); // 스택 메모리에 객체 생성
		MyTicket->SetPassengerName("Kim TaeHoon");
		MyTicket->SetNumberOfMiles(7000);
		MyTicket->SetHasEliteSuperRewardsStatus(true);
		const int Cost = MyTicket->CalPrice();
		std::cout << "Ticket Cost : " << Cost << std::endl;
	} // MyTicket 객체는 동적할당 했지만 소멸자에서 자동으로 정리된다.

	if (true)
	{
		AirlineTicket* Ptr = new AirlineTicket(); // 객체를 힙 메모리에 동적할당 
		delete Ptr; // 명시적으로 힙 메모리를 반환
	}
}