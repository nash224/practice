#pragma once
#include <memory>
#include <vector>

class Member;
class FamilyTree
{
public:
	FamilyTree() {}
	~FamilyTree() {}

	int CalculateLevel(Member* _A, Member* _B);

	template<typename... Types>
	std::shared_ptr<Member>& CreateMember(Types&&... _Args)
	{
		mTree.emplace_back(std::make_shared<Member>(std::forward<Types>(_Args)...));
		return mTree.back();
	}

	void SetRoot(std::shared_ptr<Member>& _Root)
	{
		mRoot = _Root;
	}

protected:


private:
	std::vector<std::shared_ptr<Member>> mTree;
	std::weak_ptr<Member> mRoot;

};