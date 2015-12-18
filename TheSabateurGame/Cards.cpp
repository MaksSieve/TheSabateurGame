#include "Cards.h"

Card::Card()
{
}

Card::~Card()
{
}

MountainCard::MountainCard()
{
	crashable = false;
	changable = true;
	type = mountain;
}

MineCard::MineCard()
{
	capacity = 0;
	gold = false;
	crashable = false;
	changable = true;
	type = mine;
}

MineCard::MineCard(bool g)
{
	crashable = false;
	changable = true;
	type = mine;
}

EnterCard::EnterCard()
{
	crashable = false;
	changable = false;
	type = enter;

}

TunnelCard::TunnelCard()
{
	type = tunnel;
	crashable = true;
	changable = false;
}

Wall::Wall()
{
	changable = false;
	crashable = false;
	type = wall;
}

bool MapCard::action(vector<vector<FieldCard*>>& f, pair<int, int> coord)
{
	int x = coord.first;
	int y = coord.second;
	if (!(*f[x][y]).getType() == mine)
	{
		throw;
	}
	else 
	{
		return (*f[x][y]).isGold();
	}
}