// 13_Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

// STL에서 알고리즘이란 컨테이너에서 특정 조건에 부합하는 원소에 대하여 특정 작업을 수행하는 것이다.
// STL에서는 특정 조건을 서술자(Predicate)를 함수 객체로 요구하여 알고리즘 함수 내부에서 조건에 부합하는 원소를 판별한다.

// 컨테이너의 원소를 콘솔에 출력합니다.
template<typename IterType>
void Print(IterType _Start, IterType _End)
{
	std::cout << "Print: [";

	for (; _Start != _End; ++_Start)
	{
		std::cout << (*_Start) << ' ';
	}

	std::cout << ']';
	std::cout << '\n';
}

// 전달받은 템플릿 인자의 타입을 출력합니다.
template<typename T>
void PrintType()
{
	std::cout << "Type is : " << typeid(T).name() << '\n';
}

struct MyLess
{
	bool operator()(int _lhs, int _rhs) const
	{
		return _lhs < _rhs;
	}
};

struct UserInfo
{
	UserInfo(const std::string& _Name, int _age)
		: Name(_Name)
		, Age(_age)
	{

	}

	bool operator<(const UserInfo& _Other) const 
	{
		return (_Other.Name < Name);
	}

	std::string Name;
	int Age = 0;

};

std::ostream& operator<<(std::ostream& _os, const UserInfo& _Info)
{
	_os << "Name: " << _Info.Name << ", Age: " << _Info.Age << '\n';
	return _os;
}

int main()
{
	if (false)
	{
		std::vector<int> vec;
		vec.push_back(5);
		vec.push_back(7);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(1);
		vec.push_back(9);

		std::vector<UserInfo> Infos;
		Infos.push_back({ "Kim" , 15 });
		Infos.push_back({ "Park" , 21 });
		Infos.push_back({ "Kim" , 52 });
		Infos.push_back({ "Kim" , 33 });
		Infos.push_back({ "Lee" , 5 });
		Infos.push_back({ "Kim" , 25 });

		enum { sort, partial_sort, stable_sort };
		switch (stable_sort)
		{
		case sort:
		{
			std::cout << "==== vector 정렬 수행 전 ====\n";
			Print(vec.begin(), vec.end());

			std::cout << "==== vector 정렬 수행 후 ====\n";
			std::sort(vec.begin(), vec.end(), MyLess());
			std::sort(vec.begin(), vec.end(), std::greater<int>());
			Print(vec.begin(), vec.end());
			break;
		}
		case partial_sort:
		{
			std::cout << "==== vector 정렬 수행 전 ====\n";
			Print(vec.begin(), vec.end());

			std::cout << "==== vector 정렬 수행 후 ====\n";
			// 일부만 정렬하는 함수 
			// 시작 위치로부터 2번 배열까지 정렬수행
			std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
			Print(vec.begin(), vec.end());
			break;
		}
		case stable_sort:
		{
			std::cout << "==== vector 정렬 수행 전 ====\n";
			Print(Infos.begin(), Infos.end());

			std::cout << "==== vector 정렬 수행 후 ====\n";
			// 일부만 정렬하는 함수 
			// 시작 위치로부터 2번 배열까지 정렬수행
			std::stable_sort(Infos.begin(), Infos.end());
			Print(Infos.begin(), Infos.end());
			break;
		}
		default:
			break;
		}
	}

	if (false)
	{
		// RandomAccessIterator만 sort 가능
		//std::list<int> List;
		//std::sort(List.begin(), List.end());
	}

	if (false)
	{
		std::vector<int> vec;
		vec.push_back(5);
		vec.push_back(3);
		vec.push_back(7);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(1);
		vec.push_back(3);
		vec.push_back(9);


		enum { remove_erase, if_remove };
		switch (remove_erase)
		{
		case remove_erase:
		{
			// std::remove는 배열에 조건을 만족하는 항목을 전부 뒤로 쉬프트하고, 그 위치를 반환한다.
			// 즉, remove는 원소의 이동만 할뿐 삭제되지 않는다.
			// 
			// remove함수만 사용한다면, 해당 오류구문이 출력된다. 
			// 
			// compiler output : 
			// 반환 값을 삭제하는 중: The 'remove' and 'remove_if' algorithms return the iterator past the last element that should be kept. 
			// You need to call container.erase(result, container.end()) afterwards. 
			// In C++20, 'std::erase' and 'std::erase_if' are simpler replacements for these two steps

			std::cout << "==== 벡터 원소 remove 전 ====\n";
			Print(vec.begin(), vec.end());

			std::cout << "==== 벡터 원소 remove 후 ====\n";
			vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
			Print(vec.begin(), vec.end());
			break;
		}
		case if_remove:
		{
			// remove_if를 사용하면 특정 조건에 부합하는 원소를 판별할 수 있다.

			std::cout << "==== vec 원소 ====\n";
			Print(vec.begin(), vec.end());

			std::cout << "==== 벡터에서 짝수 원소 제거 ====\n";
			// lamda는 이름없는 함수 객체를 만들 수 있다.
			// []는 캡처(capturelist)라고 하며, 외부 변수를 reference 타입이나 값을 복사하여 람다 내부에서 사용할 수 있다.
			auto EvenFunc = [](int _value) { return (_value % 2) == 0; };

			vec.erase(std::remove_if(vec.begin(), vec.end(), EvenFunc), vec.end());
			Print(vec.begin(), vec.end());
			break;
		}
		default:
			break;
		}
	}

	if (false)
	{
		std::vector<int> vec;
		vec.push_back(5);
		vec.push_back(3);
		vec.push_back(7);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(1);
		vec.push_back(3);
		vec.push_back(9);

		// std::transform : 모든 원소를 순회하며 특정 작업을 수행한다.
		// 위 함수의 3번째 인자는 복사 받을 컨테이너를 요구하는데, 
		// 해당 컨테이너는 충분한 버퍼가 할당되어 있어야한다.

		std::cout << "==== 벡터 원소 더하기 전 ====\n";
		Print(vec.begin(), vec.end());

		std::cout << "==== 더한 후 ====\n";
		auto AddOneFunc = [](int _value) { return _value + 1; };
		std::transform(vec.begin(), vec.end(), vec.begin(), AddOneFunc);
		Print(vec.begin(), vec.end());
	}

	if (true)
	{
		std::vector<int> vec;
		vec.push_back(5);
		vec.push_back(3);
		vec.push_back(7);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(1);
		vec.push_back(3);
		vec.push_back(9);
		vec.push_back(10);


		enum { find, find_if, any_of, all_of };
		switch (any_of)
		{
		case find:
		{
			// std::find는 컨테이너에 정의되어 있는 find 함수보다 느리다.
			// 해당 함수는 특별한 알고리즘 없이 순차적으로 순회하게 된다.
			const int FindValue = 7;
			std::vector<int>::iterator FIndIter = std::find(vec.begin(), vec.end(), FindValue);

			// 반보가가 가리키는 원소의 거리를 반환하는 함수
			auto dist = std::distance(vec.begin(), FIndIter);
			std::cout << "Find Value {" << FindValue << "} location is " << dist << '\n';

			// auto 타입을 추론하여 템플릿 매개변수로 전달
			PrintType<decltype(dist)>();
			break;
		}
		case find_if:
		{
			// 3의 배수를 판별하는 함수 정의
			auto lamda = [](int _value) { return (_value % 3) == 0; };

			std::vector<int>::iterator StartIter = vec.begin();
			std::vector<int>::iterator EndIter = vec.end();
			while (true)
			{
				StartIter = std::find_if(StartIter, vec.end(), lamda);
				if (StartIter == EndIter) break;

				// 반보가가 가리키는 원소의 거리를 반환하는 함수
				auto dist = std::distance(vec.begin(), StartIter);
				std::cout << "Find 3 times {" << (*StartIter) << "} location is " << dist << '\n';
				++StartIter;
			}
			break;
		}
		case any_of:
		{
			// 10의 자리수 원소를 판별한다.
			auto OverTen_func = [](int _value) { return 0 < (_value / 10); };
			auto UnderTen_func = [](int _value) { return 0 == (_value / 10); };

			// 조건에 만족하는 원소를 하나라도 존재할 경우 true 반환
			const bool bAnyElemsOverTen = std::any_of(vec.begin(), vec.end(), OverTen_func);
			const bool bAnyElemsUnderTen = std::any_of(vec.begin(), vec.end(), UnderTen_func);

			std::cout << "Is any elems over ten?: " << (bAnyElemsOverTen ? "yes" : "no") << '\n';
			std::cout << "Is any elems under ten?: " << (bAnyElemsUnderTen ? "yes" : "no") << '\n';
			break;
		}
		case all_of:
		{
			auto OverTen_func = [](int _value) { return 0 < (_value / 10); };
			auto UnderTen_func = [](int _value) { return 0 == (_value / 10); };

			// 조건에 만족하는 모든 원소를 포함할 경우 true 반환
			const bool bAllElemsOverTen = std::all_of(vec.begin(), vec.end(), OverTen_func);
			const bool bAllElemsUnderTen = std::all_of(vec.begin(), vec.end(), UnderTen_func);

			std::cout << "Is all elems over ten?: " << (bAllElemsOverTen ? "yes" : "no") << '\n';
			std::cout << "Is all elems under ten?: " << (bAllElemsUnderTen ? "yes" : "no") << '\n';
			break;
		}
		default:
			break;
		}
	}
}