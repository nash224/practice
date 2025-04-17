#pragma once
#include <stdexcept>

namespace my_std
{
	int strlen(const char* _Str)
	{
		int count = 0;
		while (true)
		{
			if ('\0' == _Str[count])
			{
				return count;
			}
			else
			{
				++count;
			}
		}

		throw std::invalid_argument("No Null character found");
		return -1;
	}

	char* strcpy(const char* _Str)
	{
		const int Len = strlen(_Str);
		char* Result = new char[Len + 1];

		for (int i = 0; i < Len + 1; i++)
		{
			Result[i] = _Str[i];
		}

		return Result;
	}

	char* strcat(const char* _Dest, const char* _Src)
	{
		const int DestLen = strlen(_Dest);
		const int SrcLen = strlen(_Src);
		char* Result = new char[DestLen + SrcLen + 1];

		for (int i = 0; i < DestLen; i++)
		{
			Result[i] = _Dest[i];
		}

		for (int i = 0; i < SrcLen + 1; i++)
		{
			Result[i + DestLen] = _Src[i];
		}

		return Result;
	}

	bool strcmp(const char* _l, const char* _r)
	{
		return (_l == _r);
	}

	bool strcmp(const char* _l, char _Arr[])
	{
		return (_l == _Arr);
	}
}
