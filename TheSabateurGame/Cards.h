#pragma once

#include <vector>

enum CardType { tunnel, action, mountain, mine, map, enter, wall };

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
	bool crashable;
	bool changable;
public:
	inline virtual bool isGold() { return false; };
	inline virtual void setGold(bool) {};
	inline virtual void setCapacity(int) {};
	inline virtual int getCapacity() { return 0; };
	inline virtual bool isCrashable() { return crashable; };
	inline virtual bool isCahngable() { return changable; };

};

class ActionCard : public Card
{
public:
	virtual bool action() { return false; };
};

class MountainCard : public FieldCard 
{
public:
	MountainCard();
};

class MineCard : public FieldCard
{
public:
	bool gold;
	int capacity;

public:
	MineCard();
	MineCard(bool g);

	inline virtual void setCapacity(int c) { capacity = c; };
	inline virtual int getCapacity() { return capacity; };
	inline virtual void setGolg(bool g) { gold = g; };
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
	MapCard() { type = map; };
	virtual bool action(vector<vector<FieldCard*>>& f, pair<int, int> coord);
};

class Wall : public FieldCard
{
public:
	Wall();
};

