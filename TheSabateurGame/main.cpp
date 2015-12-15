#include "Game.h"
#include <iostream>
#include <algorithm>

using namespace std;


void FieldPrint(Field f)
{
	for (int i = 0; i < 11; i ++)
	{
		for (int j = 0; j < 11; j++)
		{
			Card* cell = f[i][j];
			switch (cell->getType())
			{
			case mountain: {cout << "_m_"; break; };
			case mine: {cout << "_M_"; break; };
			case enter: {cout << "_E_"; break; };
			case tunnel: {cout << "___"; break; };
			case wall: {cout << "_W_"; break;}

			}
		} 
		cout << endl;
	}
}

int main() {
	Game* g = new Game();
	
	cout << "Welcome to Sabateur Game!" << endl;
	int pnum;
	try {
		cout << "Enter number of players (at least 2): ";
		cin >> pnum;
	}
	catch (std::exception e) {

	}

	string tmp_s;
	Player* tmp;
	for (int i = 0; i < pnum; i++) {
		tmp = new Player();
		cout << "Enter " << i+1 << " player's name: ";
		cin >> tmp_s;
		tmp->setName(tmp_s);
		g->players.push_back(tmp);
	}

	
	for each (Player* p in g->players)
	{
		cout << p->getName() << endl;
	}


	cout << endl;
	cout << "This is game field!" << endl;;

	FieldPrint(g->field);

	cout << "Let's start!" << endl;

	g->start();

	try 
	{
		int x;
		int y;
		while (!g->deck.empty()) 
		{
			Player& p = *g->activePlayer;
			cout << p.getName() << "'s turn!" << endl;
			cout << "Your hand: ";
			for each (Card* c in p.hand)
			{
				switch (c->getType())
				{
				case map: {cout << " M "; break; };
				case tunnel: {cout << " T "; break; };
				}
			}
			cout << endl << "Enter T to build a tunnel and M to look at map: ";
			char* s = "s";
			bool f = false;
			do
			{
				cin >> *s;
				switch (*s)
				{
				case 't':
				case 'T':
				{
					f = false;
					cout << "Enter coordinates:" << endl;
					do
					{
						try
						{
							cout << "X: ";
							cin >> x;
							cout << "Y: ";
							cin >> y;
							g->buildTunnel(p.hand.back(), pair<int, int>(x, y));
							cout << endl;
							f = false;
						}
						catch (BuildError& e)
						{
							cerr << "Can't build there! Try again!" << endl;
						}
						catch (WrongCoord& e)
						{
							cerr << "Impossible coordinates! Try again!" << endl;
						}
					} while (f);

					f = false;
					break;
				}
				case 'm':
				case 'M':
				{
					break;
				}
				default:
					f = true;
					break;
				}
			} while (f);

			FieldPrint(g->field);
			cout << endl;
			g->makeTurn();
		}
		
	}
	catch (GameOver& e) 
	{
		cout << (*e.getWinner()).getName() << " WIN!!!" << endl;
	}

	system("pause");

	return 0;
}