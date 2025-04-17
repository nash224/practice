#pragma once
#ifndef _DEFINE_LLMAX_
#define _DEFINE_LLMAX_
	constexpr size_t LL_MAX = static_cast<long long>(static_cast<unsigned long long>(-1) / 2);
#endif // !_DEFINE_LLMAX_


namespace my_std
{
	class string
	{
		typedef size_t size_type;
		typedef char value_type;
		typedef char* pointer;
		typedef const char* const_pointer;
		typedef char& reference;
		typedef const char& const_reference;

	public:
		string();
		string(const_pointer _Str);
		string(const string& _Str);
		string(string&& _Str) noexcept;
		string& operator=(const string& _Other);
		string& operator=(string&& _Other) noexcept;
		~string();

		string& operator=(const_pointer _Str);
		reference operator[](size_type _Idx) { return at(_Idx); }
		string& operator+=(const_pointer _Str);
		string& operator+=(const string& _Str);

		size_type size() const { return mSize; }
		size_type capacity() const { return mCapacity; }
		size_type length() const { size(); }
		void clear() { mSize = 0; }
		void resize(size_type _Size);
		void reserve(size_type _Size);
		bool empty() const { return (0 == mSize); }

		reference at(size_type _Idx);
		reference back();
		reference front();

		void Append(const_pointer _Str);
		void Append(string _Str);

		const_pointer c_str() const { return mPtr; }
		string substr(size_type _Off = 0, size_type _Count = LL_MAX) const;

	private:
		void _Realloc(size_type _Size);
		void _Alloc(size_type _Size);
		void _Destroy();

	private:
		size_type mSize = 0;
		size_type mCapacity = 0;
		pointer mPtr;

	};

	string operator+(const string& _lhs, const string& _rhs);
}

