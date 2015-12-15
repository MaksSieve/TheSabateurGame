#pragma once

#include "Cards.h"
#include <vector>
#include <string>

using namespace std;

enum Roles { Sabatuer, Gnome };

class Player
{
private:
	Roles role;
	string name;
	

public:
	vector<Card* > hand;
	
public:
	Player();

	inline void setName(string n) { name = n; };
	inline string getName() { return name; };
	inline void setRole(Roles r) { role = r; };
	inline Roles getRole() { return role; };

	~Player();
};

