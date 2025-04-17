#include "TextTable.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "Cell.h"


// DB�� Cell�� �ϳ��� �������� �ʴ´ٸ�, print�� ������� �ʰ� ���α׷��� �ٿ��ŵ�ϴ�.
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
