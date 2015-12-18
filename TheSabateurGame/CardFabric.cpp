#include "CardFabric.h"
#include "Game.h"
#include <ctime>
#include <algorithm>
#include <cstdlib>

CardFabric::CardFabric()
{

}

int CardFabric::operator()(vector<Card*>* d)//»нициализируем класс дл€ создани€ колоды
{
	deck = d;
	return 0;
}

vector<Card*>* CardFabric::makeNewDeck()//‘ормируем колоду
{
	for (int i = 0; i < TUNNEL_CARDS; i++)//из туннелей
	{
		Card* tmp = new TunnelCard();
		(*deck).push_back(tmp);
	}

	for (int i = 0; i < MAP_CARDS; i++)//из карт туннелей
	{
		(*deck).push_back(new MapCard());
	}

	std::srand(unsigned(std::time(0)));//тасуем колоду
	std::random_shuffle((*deck).begin(), (*deck).end());

	return deck;
}

CardFabric::~CardFabric()
{
}
