#include "Game.h"
#include <algorithm>

Game::Game(int plnum)
{
	players.reserve(8);
	players.shrink_to_fit();
	turnCount.setBorders(0, 1);
	turnCount.setStep(1);
	deck.reserve(CARDS);
	deckMaker(&deck);
}

void Game::start()
{
	activePlayer = players[0];
	deckMaker.makeNewDeck();

	for each (Player* p in players)
	{
		(*p).hand.reserve(8);
		while ((*p).hand.size() < (*p).hand.capacity())
		{
			(*p).hand.push_back(deck.back());
			deck.pop_back();
		}
	}

}


void Game::makeTurn()
{
	activePlayer = players[turnCount.next()];

	while (activePlayer->hand.size() < activePlayer->hand.capacity())
	{
		Card* tmp = (deck.back());
		activePlayer->hand.push_back(tmp);
		deck.pop_back();
	}
}

void Game::buildTunnel(Card* c, pair<int, int> coord)
{
	int x = coord.first;
	int y = coord.second;
	Player p = *activePlayer;
	if (x < 9 || y < 9 || x > -1 || y > -1){
		if (field.canBuildThere(coord))
		{
			field[x][y] = new TunnelCard();
			p.hand.erase(find(p.hand.begin(), p.hand.end(), c));
			if (field.goldFound(coord))
			{
				throw (GameOver(activePlayer));
			}
		}
		else
		{
			throw (BuildError(x, y));
		}
	}
	else
	{
		throw WrongCoord();
	}

}

Game::~Game()
{
}

Counter::Counter()
{
	_max = 0;
	_min = 0;
	_step = 0;
}

void Counter::setBorders(int left, int right)
{
	_min = left;
	_max = right;
}

void Counter::setStep(int s)
{
	_step = s;
}

int Counter::getVal()
{
	return _counter;
}

int Counter::next()
{
	if (_counter + _step <= _max)
	{
		_counter++;
	}
	else
	{
		_counter = _min;
	}
	return _counter;
}
