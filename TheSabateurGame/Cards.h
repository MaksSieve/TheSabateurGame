#pragma once

#include <vector>

enum CardType { tunnel, action, mountain, mine, map, enter, wall };//Типы возможных карт

using namespace std;

class Card 
{
protected:
	CardType type;

public:
	Card();
	virtual inline CardType getType() { return type; };
	
	~Card();
};

class FieldCard : public Card  
{
protected:
	bool crashable;//Карту можно сломать
	bool changable;//Карту можно заменить
public:
	inline virtual bool isGold() { return false; };//Наличие золота на карте
	virtual void setGold(bool g) {};//Поставить золото на карту
	inline virtual void setCapacity(int) {};//Установить емкость золота
	inline virtual int getCapacity() { return 0; };//Возвращает емкость
	inline virtual bool isCrashable() { return crashable; };//Разрушаемая и изменяемая?
	inline virtual bool isCahngable() { return changable; };

};

class ActionCard : public Card//Различные виды карт
{
public:
	virtual bool action() { return false; };
};

class MountainCard : public FieldCard 
{
public:
	MountainCard();
};

class MineCard : public FieldCard//Карта поля
{
public:
	bool gold;//Наличие золота
	int capacity;//Емкость золота

public:
	MineCard();
	MineCard(bool g);

	inline virtual void setCapacity(int c) { capacity = c; };
	inline virtual int getCapacity() { return capacity; };
	inline virtual void setGold(bool g) { gold = g; };
	inline virtual bool isGold() { return gold; };
};

class TunnelCard : public FieldCard
{
public:
	TunnelCard();
};

class EnterCard : public FieldCard
{
public:
	EnterCard();
};

class MapCard : public ActionCard
{
public:
	MapCard() { type = CardType::map; };
	virtual bool action(vector<vector<FieldCard*>>& f, pair<int, int> coord);//Применение действия на карте
};

class Wall : public FieldCard
{
public:
	Wall();
};

