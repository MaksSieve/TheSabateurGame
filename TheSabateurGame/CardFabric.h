#pragma once

#include "Cards.h"
#include <vector>

class CardFabric
{
private:
	vector<Card*>* deck;
public:
	CardFabric();
	int operator() (vector<Card*>* d);
	vector<Card*>* makeNewDeck();
	~CardFabric();
};

