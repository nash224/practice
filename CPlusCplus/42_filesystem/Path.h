#pragma once

#ifndef __DEFINE_PATH_H
#define __DEFINE_PATH_H

#include <filesystem>
#include <string_view>
#include <cassert>

// 경로(path)란, 컴퓨터가 파일 위치를 표현하는 고유한 주소
// 컴퓨터가 파일을 참조할 시, 첫 번째 경로부터 순차적으로 찾는다.
// 예를 들어, /a/b/c경로라면 /a부터 순회

// 경로를 지정하는 방식 두 가지
// 절대 경로(abolsute path)
//	- 가장 최상위 디렉토리(root directory)는  파일의 전체 경로
// 
// 상대 경로(relative path)
//	- 현재 실행되고 있는 프로그램의 위치에서 해당 파일까지의 경로
//  - 경로 앞 부분이 '.'으로 되어 있을 경우, 
// . 부분이 현재 프로그램 경로로 치환

// filesystem을 기반으로 경로 조작, 파일 경로 등의 기능을 제공합니다.
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
	// 디렉터리 확인
	_NODISCARD inline bool IsExist() const
	{
		return std::filesystem::exists(mPath);
	}
	// 상위 디렉터리 확인
	_NODISCARD inline bool IsParentPath() const
	{
		return mPath.has_parent_path();
	}

	// 하위 경로로 이동합니다.
	// 이동하는 시점에서 경로 존재 여부를 확인하지 않습니다.
	inline void MoveChild(std::string_view _Path)
	{
		mPath.append(_Path);
	}
	inline void MoveChild(std::wstring_view _Path)
	{
		mPath.append(_Path);
	}

	// 현재 경로 위치의 포인터를 반환합니다.
	inline const wchar_t* c_str() const
	{
		return mPath.c_str();
	}

	// 현재 경로 위치를 반환합니다.
	inline std::wstring GetPath() const
	{
		return std::wstring(c_str());
	}

	// 상대 경로를 반환합니다.
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


