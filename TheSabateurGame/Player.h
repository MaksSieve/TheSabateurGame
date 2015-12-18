#pragma once

#include "Cards.h"
#include <vector>
#include <string>

using namespace std;

enum Roles { Sabatuer, Gnome };//Роли в игре

class Player//Класс игрока
{
private:
	Roles role;
	string name;
	

public:
	vector<Card* > hand;//Вектор, моделирующий руку
	
public:
	Player();

	inline void setName(string n) { name = n; };//Устанавливаем имя игрока
	inline string getName() { return name; };//И возвращаем его
	inline void setRole(Roles r) { role = r; };//Установить роль игрока
	inline Roles getRole() { return role; };//И возвращаем его

	~Player();
};

