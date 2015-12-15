#pragma once

#include <exception>
#include <string>

#include "Player.h"

using namespace std;

class BuildError : public exception
{
private:
	pair<int, int> coord;
public:
	BuildError(int x, int y) { coord.first = x; coord.second = y; };

	virtual const char* what() const throw()
	{
		return "!!!ERROR!!! Cannot build there!";
	}

	pair<int, int> where() const throw()
	{
		return coord;
	}

};

class GameOver : public exception
{
private:
	Player* winner;
public:
	GameOver(Player* p) { winner = p; };

	virtual const char* what() const throw()
	{
		return "Game Over!!!";
	}

	inline Player* getWinner() { return winner; };
};

class WrongCoord : public exception
{
	virtual const char* what() const throw()
	{
		return "Wrong coordinates!!";
	}

};
