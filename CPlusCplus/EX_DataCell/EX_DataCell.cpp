// EX_DataCell.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "TextTable.h"
#include "CSVTable.h"
#include "Cell.h"
#include "Int2.h"

int main()
{
	if (false)
	{
		const int Col = 5;
		const int Row = 3;
		TextTable TTable(Row, Col);

		for (int y = 0; y < Col; y++)
		{
			for (int x = 0; x < Row; x++)
			{
				TTable.RegistCell(Table::CreateCell("TC"), x, y);
			}
		}
		std::cout << TTable.PrintTable();
	}

	if (true)
	{
		const int Col = 5;
		const int Row = 3;
		CSVTable CTable(Row, Col);

		for (int y = 0; y < Col; y++)
		{
			for (int x = 0; x < Row; x++)
			{
				CTable.RegistCell(Table::CreateCell("CC"), x, y);
			}
		}
		std::cout << CTable.PrintTable();
	}
}