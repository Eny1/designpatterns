#include "GamePC.h"

GamePC* GamePC::instance=NULL;

GamePC::GamePC(void)
{
	b=ReversiBoard::getBoardInstance();
	win=NONE;
}

GamePC* GamePC::getInstance()
{
	if(instance==NULL)
		instance=new GamePC();
	return instance;
}


void GamePC::init(std::vector<std::vector<int>>& board)
{
	board=b->GetBoardState();
	currentplayer=WHITE;
}


int GamePC::move(std::vector<std::vector<int>>& board, int i, int j)
{
	//hplayer
	if(hplayer.move(i,j))
	{
		SwitchTurn();
	}
	else
	{
		MessageBox(0,"Not valid move. Try again.","Error",0);
	}

	board=b->GetBoardState();

	return win;
}

int GamePC::computerMove(std::vector<std::vector<int>>& board)
{
	cplayer.move();
	SwitchTurn();

	board=b->GetBoardState();

	return win;
}

int GamePC::getScore(int player)
{
	return b->GetScore(player);
}

void GamePC::setComputerLevel(int t)
{
	cplayer.setLevel(t);
}

int GamePC::getPlayer()
{
	return currentplayer;
}

//change player, if player has no moves change again
void GamePC::SwitchTurn()
{
	if(IsGameOver())
		win=GetWinner();
	else
	{
		currentplayer=3-currentplayer;
		if(b->GetMoves(currentplayer).empty())
			SwitchTurn();
	}
}

//check if game is over
bool GamePC::IsGameOver()
{
	return b->IsBoardFilled() || (b->GetMoves(WHITE).empty() && b->GetMoves(BLACK).empty());
}

//check who is the winner
int GamePC::GetWinner()
{
	if(b->GetScore(WHITE)<b->GetScore(BLACK))
		return BLACK;
	return WHITE;
}

GamePC::~GamePC(void)
{
}
