#pragma once
#include "GameEngineMath.h"

// ����: ü���� ���� �߻�ȭ�� Ŭ����
// ���: 
//		1. ���忡 �����ϸ�, ������ �� �ֽ��ϴ�.
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