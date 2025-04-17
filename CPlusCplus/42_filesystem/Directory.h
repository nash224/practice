#pragma once

#ifndef __DEFINE_DIRECTORY_H
#define __DEFINE_DIRECTORY_H
#include "Path.h"
#include <vector>

class Directory : public Path
{
public:
	// from ��ο� �����ϴ� ��� ������ _to ��ο� ����
	static void Copy(std::wstring_view _from, std::wstring_view _to)
	{
		std::filesystem::copy(_from, _to, std::filesystem::copy_options::update_existing);
	}

public:
	Directory(std::filesystem::path _path = std::filesystem::current_path())
		: Path(_path)
	{

	}

	~Directory()
	{

	}

public:
	// ���丮 Ȯ��
	inline bool IsDirectory() const
	{
		return std::filesystem::is_directory(mPath);
	}

	// ���丮 ����
	bool CreateDirectory(std::wstring_view _FilePath) const;

	// ��ο� �����ϴ� ��� ��θ� ��ȯ
	_NODISCARD std::vector<std::wstring>& GetAllPath() const;
	_NODISCARD std::vector<std::wstring>& GetAllSubPath() const;

	// ��ο� �����ϴ� ��� ���丮 ����
	void RemoveAllDirectory(std::wstring_view _Path);

protected:

private:

};
#endif // !__DEFINE_DIRECTORY_H

