// EX_FamilyTree.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "FamilyTree.h"
#include "Member.h"

int main()
{
	FamilyTree Tr;
	std::shared_ptr<Member> pGrandf = Tr.CreateMember();
	std::shared_ptr<Member> pGrandm = Tr.CreateMember();
	Tr.SetRoot(pGrandm);
	Member::Marry(pGrandf, pGrandm);
	std::shared_ptr<Member> pMother = pGrandm->CreateChild(Tr);
	std::shared_ptr<Member> pFather = pGrandm->CreateChild(Tr);
	// 아.. 저 그런사람아닙니다.. 그냥 귀찮아서.. ㅜㅜㅜㅜ 어지럽네요
	Member::Marry(pFather, pMother);
	std::shared_ptr<Member> Sister = pMother->CreateChild(Tr);
	std::shared_ptr<Member> Me = pMother->CreateChild(Tr);

	// 음... GG
	Tr.CalculateLevel(Sister.get(), Me.get());
	Tr.CalculateLevel(pGrandm.get(), Me.get());
    std::cout << "Hello World!\n";
}