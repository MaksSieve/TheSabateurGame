#pragma once
//Файл исключений

#include <exception>
#include <string>

#include "Player.h"

using namespace std;

class BuildError : public exception//Ошибка построения туннеля
{
private:
	pair<int, int> coord;//пара координат
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

class GameOver : public exception//Исключение окончания игры
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

class WrongCoord : public exception//Неправильные координаты
{
	virtual const char* what() const throw()
	{
		return "Wrong coordinates!!";
	}

};
