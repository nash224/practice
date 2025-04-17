#pragma once

#ifndef __DEFINE_TABLE_H
#define __DEFINE_TABLE_H

#include <string>
#include <iostream>
#include <vector>

class Cell;

// Cell�� �����ϱ����� Ŭ����
class Table
{
public:
	// ���� �����ϰ� �ּҸ� ��ȯ�մϴ�.
	static Cell* CreateCell(const std::string& _Str = "");

public:
	Table() = delete;
	Table(int _x, int _y);
	virtual ~Table();

	/* ���̺��� ��� �� �Ӽ��� ����մϴ�. */
	virtual std::string PrintTable() const = 0;
	/* ���� ����մϴ�. */
	void RegistCell(Cell* Ptr, int row, int col);
	/* ���� ���� �����͸� ��ȯ�մϴ�. */
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


