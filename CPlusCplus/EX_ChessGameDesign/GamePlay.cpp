#include "GamePlay.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{

}

void GamePlay::GameInit()
{
	mBoard = new ChessBoard();

	mBoard->Init();
}

void GamePlay::GameEnd()
{
	delete mBoard;
}
