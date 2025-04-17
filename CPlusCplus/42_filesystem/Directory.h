#pragma once

#ifndef __DEFINE_DIRECTORY_H
#define __DEFINE_DIRECTORY_H
#include "Path.h"
#include <vector>

class Directory : public Path
{
public:
	// from 경로에 존재하는 모든 내용을 _to 경로에 복사
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
	// 디렉토리 확인
	inline bool IsDirectory() const
	{
		return std::filesystem::is_directory(mPath);
	}

	// 디렉토리 생성
	bool CreateDirectory(std::wstring_view _FilePath) const;

	// 경로에 존재하는 모든 경로를 반환
	_NODISCARD std::vector<std::wstring>& GetAllPath() const;
	_NODISCARD std::vector<std::wstring>& GetAllSubPath() const;

	// 경로에 존재하는 모든 디렉토리 제거
	void RemoveAllDirectory(std::wstring_view _Path);

protected:

private:

};
#endif // !__DEFINE_DIRECTORY_H

