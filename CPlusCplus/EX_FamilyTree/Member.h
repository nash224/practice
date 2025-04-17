#pragma once
#include <vector>
#include <memory>

class FamilyTree;
class Member : public std::enable_shared_from_this<Member>
{
public:
	static void Marry(std::shared_ptr<Member>& _G, std::shared_ptr<Member>& _B);

public:
	void AddParent(const std::shared_ptr<Member>& parent);
	void AddSpouse(const std::shared_ptr<Member>& spouse);
	void AddChild(const std::shared_ptr<Member>& child);


	std::shared_ptr<Member>& CreateChild(FamilyTree& _Tree);
	std::shared_ptr<Member> GetSharedPtr() { return shared_from_this(); }

private:
	std::vector<std::shared_ptr<Member>> mChildren;
	std::vector<std::weak_ptr<Member>> mParents;
	std::weak_ptr<Member> mSpouse;
};
