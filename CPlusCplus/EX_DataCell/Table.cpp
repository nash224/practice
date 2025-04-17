#include "Table.h"
#include <cassert>

#include "Cell.h"

Cell* Table::CreateCell(const std::string& _Str /*= ""*/)
{
	Cell* NewCell = new Cell(_Str);
	return NewCell;
}

Table::Table(int _x, int _y)
{
	// DB 확장
	DataBase.resize(_y);
	for (int i = 0; i < _y; i++)
	{
		DataBase[i].resize(_x);
	}

	// 각 칸에 생성
	for (int y = 0; y < _y; y++)
	{
		for (int x = 0; x < _x; x++)
		{
			DataBase[y][x] = CreateCell();
		}
	}
}

Table::~Table()
{
	for (std::vector<Cell*>& Col : DataBase)
	{
		for (Cell* pCell : Col)
		{
			if (nullptr != pCell)
			{
				delete pCell;
				pCell = nullptr;
			}
		}
	}
}

void Table::RegistCell(Cell* Ptr, int row, int col)
{
	assert(nullptr != Ptr);

	assert(!IsOver(row, col));

	if (nullptr != DataBase[col][row])
	{
		delete DataBase[col][row];
	}

	DataBase[col][row] = Ptr;
}

std::string& Table::GetCell(int row, int col)
{
	assert(!IsOver(row, col));

	assert(nullptr != DataBase[col][row]);
	
	return DataBase[col][row]->Get();
}

bool Table::IsOver(int row, int col) const
{
	const int COL_SIZE = static_cast<int>(DataBase.size());
	const int ROW_SIZE = static_cast<int>(DataBase[0].size());
	const bool bOverBuffer = (COL_SIZE < 0 || COL_SIZE < col) || (ROW_SIZE < 0 || ROW_SIZE < row);
	return bOverBuffer;
}
