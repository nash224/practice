#pragma once
#include <vector>

#include "Employee.h"

// ��� :
//	�������� ���Ǹ� ���ο� ��� ��ȣ�� �ο��Ͽ� ��ȯ�ϴ� ���.
//	��� ���� ���ڵ��� ������̸�, ��ü ������ ���� ��ϰ� ������� ���� �Ǵ� ������ ������ ������ ����ϴ� ���.

/* �����ͺ��̽� Ŭ������ ������ ��ü�� �迭�� ��� �����Ѵ�. */

namespace Records
{
	const int kFirstEmployeeNumber = 1000;

	class DataBase
	{
	public:
		DataBase();
		~DataBase();

		/* ������ �Է��Ͽ� ���� ������ �߰��Ѵ�. */
		Employee& AddEmployee(const std::string& _FirstName, const std::string& _LastName);
		/* �Էµ� ������ ������ ��ȯ�Ѵ�. */
		Employee& GetEmployee(const std::string& _FirstName, const std::string& _LastName);
		/* �Էµ� ������ ������ ��ȯ�Ѵ�. */
		Employee& GetEmployee(int _Number);

		/* ��ü ������ ���� ������ ����Ѵ�. */
		void DisplayAll() const;
		/* ���� ������ ���� ������ ����Ѵ� */
		void DisplayCurrent() const;
		/* �ذ�� ������ ���� ������ ����Ѵ� */
		void DisplayFormer() const;

	protected:

	private:
		/* ������ ���� ���ڵ� ���� */
		std::vector<Employee> mEmployees;
		/* ������ �������� �Ҵ��� ���� ��ȣ */
		int mNextEmployeeNumber;

	};
}
