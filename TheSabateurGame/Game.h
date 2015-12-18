#pragma once

#include "Player.h"
#include "Cards.h"
#include "Field.h"
#include "Exceptions.h"
#include "CardFabric.h"

#include <vector>

using namespace std;

const int CARDS = 80;
const int TUNNEL_CARDS = 76;
const int MAP_CARDS = 4;

class Counter 
{
private:
	int _counter;
	int _max;
	int _min;
	int _step;

public:
	Counter();
	void setBorders(int left, int right);
	void setStep(int s);
	int getVal();
	int next();
};

class Game
{
public:
	vector<Player*> players;//вектор игроков
	vector<Card*> deck;//Вектор колоды
	Field field;//Поле игры
	Counter turnCount;//Количестов ходов
	Player* activePlayer;//Указатель на активного игрока
	CardFabric deckMaker;//Экземляр тасующего класса

public:
	Game(int);
	void start();	// инициализирует начало игры
	void makeTurn();	// передает ход следующему игроку, добавляет карты
	void buildTunnel(Card* c, pair<int, int>);	//строит туннель заданым игроком
	void makeAction(Player& reciever, ActionCard* c); //совершает действие над другим игроком
	bool lookMap(MapCard* c, pair<int, int>); //смотрит на карту
	~Game();
};

