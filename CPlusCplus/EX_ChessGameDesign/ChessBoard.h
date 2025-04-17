#pragma once
#include <vector>

#include "GameEngineMath.h"
#include "ChessPiece.h"

// 목적: 게임에 필요한 체스 보드 클래스
// 기능: 
//		1. 체스판 좌표를 제공합니다.
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

	/* 해당 위치의 말을 가져옵니다. */
	ChessPiece* GetPieceAt(const Int2& _Pos)
	{
		return (*this)[_Pos.Y][_Pos.X];
	}

	/* 해당 좌표 값이 EMPTY인 경우, true 를 반환합니다. */
	bool IsEmpty(const Int2& _Pos) const { return EMPTY == At(_Pos); }

protected:

private:

};