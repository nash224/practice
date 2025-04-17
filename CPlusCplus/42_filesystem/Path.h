#pragma once

#ifndef __DEFINE_PATH_H
#define __DEFINE_PATH_H

#include <filesystem>
#include <string_view>
#include <cassert>

// ���(path)��, ��ǻ�Ͱ� ���� ��ġ�� ǥ���ϴ� ������ �ּ�
// ��ǻ�Ͱ� ������ ������ ��, ù ��° ��κ��� ���������� ã�´�.
// ���� ���, /a/b/c��ζ�� /a���� ��ȸ

// ��θ� �����ϴ� ��� �� ����
// ���� ���(abolsute path)
//	- ���� �ֻ��� ���丮(root directory)��  ������ ��ü ���
// 
// ��� ���(relative path)
//	- ���� ����ǰ� �ִ� ���α׷��� ��ġ���� �ش� ���ϱ����� ���
//  - ��� �� �κ��� '.'���� �Ǿ� ���� ���, 
// . �κ��� ���� ���α׷� ��η� ġȯ

// filesystem�� ������� ��� ����, ���� ��� ���� ����� �����մϴ�.
class Path
{
public:
	static inline _NODISCARD bool IsExist(std::wstring_view _Path)
	{
		return std::filesystem::exists(_Path);
	}
	static inline _NODISCARD bool IsExist(const std::filesystem::path& _Path)
	{
		return std::filesystem::exists(_Path);
	}
	static inline _NODISCARD bool IsExist(const std::filesystem::path& _Path, std::wstring_view _ChildPath)
	{
		return IsExist(_Path / _ChildPath);
	}

public:
	Path(std::filesystem::path _path 
		= std::filesystem::current_path())
		: mPath(_path)
	{

	}

	~Path() {}

	inline operator std::filesystem::path()
	{
		return mPath;
	}

	inline void operator=(std::string_view _sv)
	{
		mPath = _sv;
	}

	inline Path& operator+=(std::string_view _sv)
	{
		MoveChild(_sv);
		return *this;
	}

	inline Path& operator+=(std::wstring_view _wsv)
	{
		MoveChild(_wsv);
		return *this;
	}

public:
	// ���͸� Ȯ��
	_NODISCARD inline bool IsExist() const
	{
		return std::filesystem::exists(mPath);
	}
	// ���� ���͸� Ȯ��
	_NODISCARD inline bool IsParentPath() const
	{
		return mPath.has_parent_path();
	}

	// ���� ��η� �̵��մϴ�.
	// �̵��ϴ� �������� ��� ���� ���θ� Ȯ������ �ʽ��ϴ�.
	inline void MoveChild(std::string_view _Path)
	{
		mPath.append(_Path);
	}
	inline void MoveChild(std::wstring_view _Path)
	{
		mPath.append(_Path);
	}

	// ���� ��� ��ġ�� �����͸� ��ȯ�մϴ�.
	inline const wchar_t* c_str() const
	{
		return mPath.c_str();
	}

	// ���� ��� ��ġ�� ��ȯ�մϴ�.
	inline std::wstring GetPath() const
	{
		return std::wstring(c_str());
	}

	// ��� ��θ� ��ȯ�մϴ�.
	inline std::wstring Relative() const
	{
		return mPath.relative_path();
	}

protected:
	inline void ValidCheck() const
	{
		assert(true == IsExist());
	}

protected:
	std::filesystem::path mPath;

};

#endif // !__DEFINE_PATH_H


