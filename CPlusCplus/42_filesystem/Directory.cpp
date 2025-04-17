#include "Directory.h"
#include <cassert>

_NODISCARD
bool Directory::CreateDirectory(std::wstring_view _FilePath) const
{
	return std::filesystem::create_directories(mPath / _FilePath);
}

std::vector<std::wstring>& Directory::GetAllPath() const
{
	ValidCheck();

	static std::vector<std::wstring> ReturnValue;
	ReturnValue.clear();

	// ���͸� ���� �ݺ��ڷ� ���� ��ο� �ִ� ��� ��� ��ȸ
	std::filesystem::directory_iterator DirIter(mPath);
	while (std::filesystem::end(DirIter) != DirIter)
	{
		const std::filesystem::directory_entry& Entry = (*DirIter);
		ReturnValue.emplace_back(Entry.path());
		++DirIter;
	}

	return ReturnValue;
}

_NODISCARD std::vector<std::wstring>& Directory::GetAllSubPath() const
{
	ValidCheck();

	static std::vector<std::wstring> ReturnValue;
	ReturnValue.clear();

	// ���͸� ���� �ݺ��ڷ� ���� ��ο� �ִ� ��� ��� ��ȸ
	std::filesystem::recursive_directory_iterator DirIter(mPath);
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		ReturnValue.emplace_back(Entry.path());
	}

	return ReturnValue;
}

void Directory::RemoveAllDirectory(std::wstring_view _Path)
{
	std::filesystem::path Path = mPath / _Path;
	if (false == IsExist(Path))
	{
		return;
	}

	std::filesystem::remove_all(Path);
}
