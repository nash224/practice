#pragma once

#ifndef __DEFINE_TEXT_TABLE_H
#define __DEFINE_TEXT_TABLE_H
#include "Table.h"

#include <string>


class TextTable : public Table
{
public:
	TextTable(int _x, int _y)
		: Table(_x, _y)
	{

	}

	std::string PrintTable() const override;

};

#endif // !__DEFINE_TEXT_TABLE_H
