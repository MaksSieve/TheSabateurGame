#pragma once

#include "Cards.h"
#include <vector>

using namespace std;

class Field : public vector<vector<FieldCard*>>//Класс поля
{
public:
	Field();
	bool canBuildThere(pair<int, int>);
	bool goldFound(pair<int, int>);
	const size_t MIN_DIMENSION = 11;//Минимальная размерность квадратного поля

	~Field();
};

