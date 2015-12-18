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
	vector<Player*> players;
	vector<Card*> deck;
	Field field;
	Counter turnCount;
	Player* activePlayer;
	CardFabric deckMaker;




public:
	Game(int);
	void start();	// �������������� ������ ����
	void makeTurn();	// �������� ��� ���������� ������, ��������� �����
	void buildTunnel(Card* c, pair<int, int>);	//������ ������� ������� �������
	void makeAction(Player& reciever, ActionCard* c); //��������� �������� ��� ������ �������
	bool lookMap(MapCard* c, pair<int, int>); //������� �� �����
	~Game();
};

