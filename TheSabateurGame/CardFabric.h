#pragma once

#include "Cards.h"
#include <vector>

class CardFabric//формирует колоду карт
{
private:
	vector<Card*>* deck;//”казатель на колоду
public:
	CardFabric();
	int operator() (vector<Card*>* d);
	vector<Card*>* makeNewDeck();
	~CardFabric();
};

