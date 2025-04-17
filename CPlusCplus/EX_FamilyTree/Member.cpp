#include "Member.h"
#include <cassert>

#include "FamilyTree.h"

void Member::Marry(std::shared_ptr<Member>& _G, std::shared_ptr<Member>& _B)
{
	assert(nullptr != _G && nullptr != _B);

	_G->AddSpouse(_B);
	_B->AddSpouse(_G);
}

std::shared_ptr<Member>& Member::CreateChild(FamilyTree& _Tree)
{
	if (true == mSpouse.expired())
	{
		static std::shared_ptr<Member> ReturnValue;
		return ReturnValue;
	}

	std::shared_ptr<Member>& NewChild = _Tree.CreateMember();
	AddChild(NewChild);
	mSpouse.lock()->AddChild(NewChild);
	NewChild->AddParent(GetSharedPtr());
	NewChild->AddParent(mSpouse.lock());
	return NewChild;
}

void Member::AddParent(const std::shared_ptr<Member>& parent)
{
	mParents.push_back(parent);
}

void Member::AddSpouse(const std::shared_ptr<Member>& spouse)
{
	mSpouse = spouse;
}

void Member::AddChild(const std::shared_ptr<Member>& child)
{
	mChildren.push_back(child);
}
