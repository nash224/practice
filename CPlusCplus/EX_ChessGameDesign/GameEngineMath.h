#pragma once


struct Int2
{
public:
	int X;
	int Y;

	Int2(int _X, int _Y)
		: X(_X)
		, Y(_Y)
	{

	}

	Int2 Add(int _X, int _Y) const
	{
		return Int2(X + _X, Y + _Y);
	}

	Int2 Add(const Int2& _Other) const
	{
		return Add(_Other.X, _Other.Y);
	}

private:


};
