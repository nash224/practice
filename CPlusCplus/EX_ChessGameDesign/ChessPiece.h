#pragma once
#include "GameEngineMath.h"

// 목적: 체스의 말을 추상화한 클래스
// 기능: 
//		1. 보드에 존재하며, 움직일 수 있습니다.
class ChessPiece
{
public:
	ChessPiece();
	~ChessPiece();

	void Init() {}
	void Move(const Int2& _Pos) {}

protected:

private:
	Int2 Pos;

};