#pragma once

#ifndef __DEFINE_CELL_H
#define __DEFINE_CELL_H

#include <string>
#include <iostream>
#include "Int2.h"

class Table;

class Cell
{
public:
	Cell(const std::string& data) : mData(data) {};

	inline std::string& Get() { return mData; };

private:
	Table* mParent = nullptr; // 어느 테이블에 속해있는지
	std::string mData;
	Int2 Pos;

public:
	friend class Table;
	friend std::ostream& operator<<(std::ostream& os, const Cell& _Cell);

};

inline std::ostream& operator<<(std::ostream& os, const Cell& _Cell)
{
	os << _Cell.mData;
	return os;
}


#endif // !__DEFINE_CELL_H
