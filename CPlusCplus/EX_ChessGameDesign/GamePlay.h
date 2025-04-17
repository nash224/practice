#pragma once
#include <array>

#include "ChessBoard.h"

constexpr int PlayerCount = 2;

// ����: ���� ������ ������ �����մϴ�.
class GamePlay
{
public:
	GamePlay();
	~GamePlay();

	/* ������ �����ϱ����� �����۾��� �����մϴ�. */
	void GameInit();
	/* ������ �����մϴ�. */
	void GameStart();
	/* ������ ������Ʈ�մϴ�. */
	void GameUpdate();
	/* ������ �����ϴ� */
	void GameEnd();

private:
	// class ���漱���� ����� ���� ����� ������� �ʽ��ϴ�.
	ChessBoard* mBoard;
	std::array<Player, PlayerCount> mPlayers;

};