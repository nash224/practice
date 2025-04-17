#pragma once
#include <vector>

#include "Employee.h"

// 기능 :
//	종업원이 고용되면 새로운 사원 번호를 부여하여 반환하는 기능.
//	모든 직원 레코드의 저장소이며, 전체 직원에 대한 목록과 고용중인 직원 또는 퇴직한 직원의 정보를 출력하는 기능.

/* 데이터베이스 클래스는 종업원 객체를 배열에 담아 관리한다. */

namespace Records
{
	const int kFirstEmployeeNumber = 1000;

	class DataBase
	{
	public:
		DataBase();
		~DataBase();

		/* 정보를 입력하여 고용된 직원을 추가한다. */
		Employee& AddEmployee(const std::string& _FirstName, const std::string& _LastName);
		/* 입력된 정보로 직원을 받환한다. */
		Employee& GetEmployee(const std::string& _FirstName, const std::string& _LastName);
		/* 입력된 정보로 직원을 받환한다. */
		Employee& GetEmployee(int _Number);

		/* 전체 직원에 대한 정보를 출력한다. */
		void DisplayAll() const;
		/* 고용된 직원에 대한 정보를 출력한다 */
		void DisplayCurrent() const;
		/* 해고된 직원에 대한 정보를 출력한다 */
		void DisplayFormer() const;

	protected:

	private:
		/* 직원에 대한 레코드 모음 */
		std::vector<Employee> mEmployees;
		/* 직원이 고용됐을때 할당할 고유 번호 */
		int mNextEmployeeNumber;

	};
}
