#pragma once
#include <string>

// 종업원의 데이터를 추상화한다.
// 헤더파일에는 클래스가 수행할 행동을 정의한다.

namespace Records
{
	// Record namespace 밖이라면 명식적으로 지정해야 접근이 가능하다.
	const int kDefaultStartingSalary = 30000;

	class Employee
	{
	public:
		Employee();
		~Employee();

		// 디폴트 파라미터는 메서드 호출자에 넘겨줄 인자가 공백이라면
		// 디폴트로 설정된 값이 자동으로 넘겨진다.

		/* 종업원의 연봉을 인상한다 */
		void Promote(int _RaiseAmount = 1000);

		/* 종업원의 연봉을 감봉한다 */
		void Demote(int _DemeritAmount = 1000);
		/* 종업원을 고용한다. */
		void Hire();
		/* 종업원을 해고한다. */
		void Fire();
		/* 종업원의 정보를 출력한다. */
		void Display() const;

		void SetFirstName(const std::string& _FirstName);
		const std::string& GetFirstName() const;

		void SetLastName(const std::string& _LastName);
		const std::string& GetLastName() const;

		void SetEmployeeNumber(int _Number);
		int GetEmployeeNumber() const;

		void SetSalary(int _Number);
		int GetSalary() const;

		bool IsHired() const;

	protected:

	private:
		// private 데이터는 클래스 외부에서 보이지 않는다.
		// 해당 데이터에 접근하려면 Getter와 Setter 로 접근해야 한다.
		std::string mFirstName;
		std::string mLastName;
		int mEmployeeNumber;
		int mSalary;
		bool mHired;

	};
}
