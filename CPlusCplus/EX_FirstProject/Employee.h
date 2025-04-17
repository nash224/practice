#pragma once
#include <string>

// �������� �����͸� �߻�ȭ�Ѵ�.
// ������Ͽ��� Ŭ������ ������ �ൿ�� �����Ѵ�.

namespace Records
{
	// Record namespace ���̶�� ��������� �����ؾ� ������ �����ϴ�.
	const int kDefaultStartingSalary = 30000;

	class Employee
	{
	public:
		Employee();
		~Employee();

		// ����Ʈ �Ķ���ʹ� �޼��� ȣ���ڿ� �Ѱ��� ���ڰ� �����̶��
		// ����Ʈ�� ������ ���� �ڵ����� �Ѱ�����.

		/* �������� ������ �λ��Ѵ� */
		void Promote(int _RaiseAmount = 1000);

		/* �������� ������ �����Ѵ� */
		void Demote(int _DemeritAmount = 1000);
		/* �������� ����Ѵ�. */
		void Hire();
		/* �������� �ذ��Ѵ�. */
		void Fire();
		/* �������� ������ ����Ѵ�. */
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
		// private �����ʹ� Ŭ���� �ܺο��� ������ �ʴ´�.
		// �ش� �����Ϳ� �����Ϸ��� Getter�� Setter �� �����ؾ� �Ѵ�.
		std::string mFirstName;
		std::string mLastName;
		int mEmployeeNumber;
		int mSalary;
		bool mHired;

	};
}
