// DateApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <assert.h>

class Date
{
private:
	static const int MAX_MONTH = 12;

public:
	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	void ShowDate() const;

private:
	// 날짜를 업데이트 합니다.
	void DateUpdate();

private:
	int mYear;
	int mMonth; // 1 부터 12 까지.
	int mDay; // 1 부터 31 까지.

};

int main()
{
	Date DateObject;
	DateObject.SetDate(2025, 2, 28);
	DateObject.ShowDate();
	DateObject.SetDate(2023, 3, 2802);
	DateObject.ShowDate();
}

void Date::SetDate(int year, int month, int date)
{
	mYear = year;
	mMonth = month - 1;
	mDay = date - 1;

	DateUpdate();
}

void Date::AddDay(int inc)
{
	mDay += inc;
	DateUpdate();
}

void Date::AddMonth(int inc)
{
	mMonth += inc;
	DateUpdate();
}

void Date::AddYear(int inc)
{
	mYear += inc;
}

void Date::ShowDate() const
{
	std::cout << "Date : " << mYear << "/" << (mMonth + 1) << "/" << (mDay + 1) << '\n';
}

void Date::DateUpdate()
{
	mMonth = mMonth % MAX_MONTH;
	mYear += mMonth / MAX_MONTH;

	static const int DatePerMonth[MAX_MONTH] =
	{
		31,28,31,30,31,30,31,31,30,31,30,31
	};

	for (; ;)
	{
		assert(0 <= mMonth && mMonth < MAX_MONTH);

		if (mDay < DatePerMonth[mMonth])
		{
			break;
		}

		mDay -= DatePerMonth[mMonth];
		++mMonth;

		if (MAX_MONTH <= mMonth)
		{
			mMonth -= MAX_MONTH;
			++mYear;
		}
	}
}
