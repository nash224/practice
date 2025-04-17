// 42_filesystem.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Directory.h"

// c++ 17이상부터 가능
// file system - 파일과 디렉토리를 다룰 수 있도록 제공해줌
// 파일 쓰기, 읽기 수행 x

// 예를들어, 경로에 있는 파일을 찾거나 경로를 생성할 수 있고,
// 파일에 대한 메타 정보(수정일자, 크기, 권한)를 얻어낼 수 있음

int main()
{
	Directory Dir;
	Dir += "Resources";
	Dir += "Test.txt";

	std::wcout << "[" << Dir.GetPath() << "] is exist? : " << std::boolalpha << Dir.IsExist() << '\n';
	/* otuput: [C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Resources\Test.txt] is exist ? : true*/ 
	std::wcout << "relative path: [" << Dir.Relative() << "] \n";
	/* output: relative path: [CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Resources\Test.txt] */

	Dir = std::filesystem::current_path();
	std::vector<std::wstring>& Dirs = Dir.GetAllPath();
	for (auto& Dir : Dirs)
	{
		std::wcout << Dir.c_str() << '\n';
	}
	/* output:
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\42_filesystem.cpp
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\42_filesystem.vcxproj
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\42_filesystem.vcxproj.filters
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\42_filesystem.vcxproj.user
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Directory.cpp
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Directory.h
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Path.cpp
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Path.h
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\Resources
	C:\CPlusPlus\MyProject\MyLib\CPlusCplus\42_filesystem\x64
	*/

	Dirs = Dir.GetAllSubPath();

	const std::wstring ChildPath = LR"(Resources\Map\1\2\3S)";
	if (false == Path::IsExist(Dir, ChildPath))
	{
		Dir.CreateDirectory(ChildPath);
	}

	Dir.RemoveAllDirectory(LR"(Resources\Map)");
}