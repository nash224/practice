#pragma once
#include <vector>

#include "GameEngineMath.h"
#include "ChessPiece.h"

// ����: ���ӿ� �ʿ��� ü�� ���� Ŭ����
// ���: 
//		1. ü���� ��ǥ�� �����մϴ�.
//		2. 

template <typename T>
class GameBoard
{
public:
	std::vector<T>& operator[](int _Index) { return Board.at(_Index); }

	void Init() {}
	void Update() {}
	void Release() {}

protected:
	inline T& At(const Int2& _Pos) { return Board[_Pos.Y][_Pos.X]; }
	inline const T& At(const Int2& _Pos) const { return Board[_Pos.Y][_Pos.X]; }
	void AllocBoard(const Int2& _Size)
	{
		const int Height = _Size.Y;
		const int Width = _Size.Y;
		Board.resize(Height);
		for (std::vector<T>& i : Board)
		{
			i.resize(Width);
		}
	}
	void FillBoard(const T& _Data)
	{
		if (true == Board.empty() || true == Board[0].empty())
		{
			throw;
		}

		for (std::vector& Vec : Board)
		{
			for (T& Data : Vec)
			{
				Data = _Data;
			}
		}
	}

protected:
	std::vector<std::vector<T>> Board;

private:

};

class ChessBoard : GameBoard<ChessPiece*>
{
public:
	static constexpr ChessPiece* EMPTY = nullptr;

public:
	ChessBoard();
	~ChessBoard();

	void Init()
	{
		AllocBoard(Int2(8, 8));
		FillBoard(nullptr);
	}

	/* �ش� ��ġ�� ���� �����ɴϴ�. */
	ChessPiece* GetPieceAt(const Int2& _Pos)
	{
		return (*this)[_Pos.Y][_Pos.X];
	}

	/* �ش� ��ǥ ���� EMPTY�� ���, true �� ��ȯ�մϴ�. */
	bool IsEmpty(const Int2& _Pos) const { return EMPTY == At(_Pos); }

protected:

private:

};