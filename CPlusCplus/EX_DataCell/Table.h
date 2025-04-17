#pragma once

#ifndef __DEFINE_TABLE_H
#define __DEFINE_TABLE_H

#include <string>
#include <iostream>
#include <vector>

class Cell;

// Cell을 관리하기위한 클래스
class Table
{
public:
	// 셀을 생성하고 주소를 반환합니다.
	static Cell* CreateCell(const std::string& _Str = "");

public:
	Table() = delete;
	Table(int _x, int _y);
	virtual ~Table();

	/* 테이블의 모든 셀 속성을 출력합니다. */
	virtual std::string PrintTable() const = 0;
	/* 셀을 등록합니다. */
	void RegistCell(Cell* Ptr, int row, int col);
	/* 셀의 내부 데이터를 반환합니다. */
	std::string& GetCell(int row, int col);

private:
	bool IsOver(int row, int col) const;

protected:
	std::vector<std::vector<Cell*>> DataBase;
};

inline std::ostream& operator<<(std::ostream& os, const Table& t)
{
	os << t.PrintTable();
	return os;
}

#endif // !__DEFINE_TABLE_H


