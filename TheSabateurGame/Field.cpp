#include "Field.h"
#include <cstdlib>

Field::Field()
{
	int dim = MIN_DIMENSION - 1;
	(*this).resize(MIN_DIMENSION);
	for (size_t i = 0; i < MIN_DIMENSION; i++)
	{
		(*this)[i].resize(MIN_DIMENSION);
		for (size_t j = 0; j < MIN_DIMENSION; j++)
		{	
			if (i == 5 && j == 5)
			{
				(*this)[i][j] = new EnterCard();
			}
			else
			{
				if (i == 0 || j == 0 || i == 10 || j == 10)
				{
					(*this)[i][j] = new Wall();
				}
				else
				{
					(*this)[i][j] = new MountainCard();
				}
			}
		}
	}
	(*this)[1][1] = new MineCard();
	(*this)[1][9] = new MineCard();
	(*this)[9][1] = new MineCard();
	(*this)[9][9] = new MineCard();

	switch (rand()%4+1)
	{
	case 1: {(*(*this)[1][1]).setGold(true); (*(*this)[1][1]).setCapacity(rand() % 3 + 1); break;}
	case 2: {(*(*this)[1][9]).setGold(true); (*(*this)[1][9]).setCapacity(rand() % 3 + 1); break;}
	case 3: {(*(*this)[9][1]).setGold(true); (*(*this)[9][1]).setCapacity(rand() % 3 + 1); break;}
	case 4: {(*(*this)[9][9]).setGold(true); (*(*this)[9][9]).setCapacity(rand() % 3 + 1); break;}
	default:
		break;
	}
}

bool Field::canBuildThere(pair<int, int> coord)
{
	Field f = *this;
	int x = coord.first;
	int y = coord.second;
	
	return ((f[x - 1][y]->getType() == tunnel)||(f[x + 1][y]->getType() == tunnel)
		||(f[x][y + 1]->getType() == tunnel)||(f[x][y + 1]->getType() == tunnel)
		|| (f[x][y + 1]->getType() == enter) || (f[x][y - 1]->getType() == enter)
		|| (f[x + 1][y]->getType() == enter) || (f[x - 1][y]->getType() == enter))
		&& (f[x][y]->isCahngable());

}

bool Field::goldFound(pair<int, int> coord)
{
	Field f = *this;
	int x = coord.first;
	int y = coord.second;
	return (f[x - 1][y]->getType() == mine) && ((f[x - 1][y])->isGold())
		 ||(f[x + 1][y]->getType() == mine) && ((f[x + 1][y])->isGold())
		 ||(f[x][y - 1]->getType() == mine) && ((f[x][y - 1])->isGold())
		 ||(f[x][y + 1]->getType() == mine) && ((f[x][y + 1])->isGold());
}

Field::~Field()
{
}
