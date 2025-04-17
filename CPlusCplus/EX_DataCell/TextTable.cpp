#include "TextTable.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "Cell.h"


// DB에 Cell이 하나라도 생성되지 않는다면, print를 허용하지 않고 프로그램을 다운시킵니다.
std::string TextTable::PrintTable() const
{
	static std::stringstream ss;
	ss.clear();

	for (const std::vector<Cell*>& Col : DataBase)
	{
		for (const Cell* pCell : Col)
		{
			assert(nullptr != pCell);
			ss << (*pCell);
		}

		ss << '\n';
	}

	return ss.str();
}
