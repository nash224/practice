#pragma once
#include <array>

#include "ChessBoard.h"

constexpr int PlayerCount = 2;

// 목적: 게임 관리자 역할을 수행합니다.
class GamePlay
{
public:
	GamePlay();
	~GamePlay();

	/* 게임을 시작하기위해 사전작업을 수행합니다. */
	void GameInit();
	/* 게임을 시작합니다. */
	void GameStart();
	/* 게임을 업데이트합니다. */
	void GameUpdate();
	/* 게임을 끝냅니다 */
	void GameEnd();

private:
	// class 전방선언은 배우지 않은 관계로 사용하지 않습니다.
	ChessBoard* mBoard;
	std::array<Player, PlayerCount> mPlayers;

};