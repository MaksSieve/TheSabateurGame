#include <SFML/Graphics.hpp>
#include "TheSabateurGame\TheSabateurGame\Game.h"

using namespace sf;

void drawmap(Game*, Sprite, RenderWindow&);

int main()
{
	Clock clock;
	Game* g = new Game();
	RenderWindow window(VideoMode(32*9, 32*9+50), "The Saboteur");
	Image mymap;
	mymap.loadFromFile("map.png");
	Texture mmap;
	mmap.loadFromImage(mymap);
	Sprite s_map;
	s_map.setTexture(mmap);
	Font font;
	font.loadFromFile("arial.ttf");
	Text text("", font, 20);
	text.setColor(Color::Red);
	text.setPosition(0, window.getSize().y - 50);
	Text text2("", font, 20);
	text2.setColor(Color::Red);
	text2.setPosition(0, 0);
	int pnum = 0;
//	string tmp_s[2] = { "dm", "mks" };
	Player* tmp;
	/*for (int i = 0; i < pnum; i++) 
	{
		tmp = new Player();
		tmp->setName(tmp_s[i]);
		g->players.push_back(tmp);
	}*/
	
	string name;
	bool infonotentered=1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
					name+= static_cast<char>(event.text.unicode);
			}
		}
		window.clear();
		if (infonotentered) 
		{
			int plnum = 1;
			if (plnum - 1)
				text2.setString("Enter player " + to_string(plnum - 1) + " name: " + name);
			else
				text2.setString("Enter number of players: " + name);
			window.draw(text2);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Tilde)) {
				switch (plnum) {
				case 1: {
					pnum = stoi(name);
					plnum++;
					name = "";
					break;
				}
				default:{
					tmp = new Player();
					tmp->setName(name);
					g->players.push_back(tmp);
					plnum++;
					name = "";
					break;
				}
				}
				if (plnum - 1 == pnum) {
					infonotentered = 0;
					g->start();
				}
			}
		}
		else
		{
			drawmap(g, s_map, window);
			text.setString("Current Player: " + g->activePlayer->getName());
			window.draw(text);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i pos = Mouse::getPosition(window);
				try
				{
					//while (!g->deck.empty()) 
					//{
					try
					{
						g->buildTunnel(g->activePlayer->hand.back(), pair<int, int>((pos.x) / 32 + 1, (pos.y) / 32 + 1));
						g->makeTurn();
					}
					catch (BuildError &e)
					{

					}

					//}

				}
				catch (GameOver& e)
				{
					text.setString(e.getWinner()->getName() + " WIN!!!\nPress space to exit.");
					window.clear();
					drawmap(g, s_map, window);
					window.draw(text);
					window.display();
					clock.restart();
					while (1)
					{
						if (Keyboard::isKeyPressed(Keyboard::Space))
							break;
					}
					break;
				}
			}
			window.display();
			clock.restart();
			while (clock.getElapsedTime().asSeconds() <= 0.05)
			{

			}
		}
	}
	return 0;
}

void drawmap(Game* g, Sprite s_map, RenderWindow& window)
{
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j <9; j++) 
		{
			Card* cell = g->field[i + 1][j + 1];
			switch (cell->getType())
			{
			case mountain: 
			{
				s_map.setTextureRect(IntRect(32, 0, 32, 32));
				break;
			};
			case mine: 
			{
				s_map.setTextureRect(IntRect(64, 0, 32, 32));
				break;
			};
			case enter: 
			{
				s_map.setTextureRect(IntRect(96, 0, 32, 32));
				break;
			};
			case tunnel:
			{
				s_map.setTextureRect(IntRect(0, 0, 32, 32));
				break;
			};
			}
			s_map.setPosition(i * 32, j * 32);
			window.draw(s_map);
		}
	}
}

/*

try
{
while (!g->deck.empty())
{
try
{
cout << g->activePlayer->getName() << "'s turn!" << endl;
int x;
int y;
cin >> x;
cin >> y;
g->buildTunnel(g->activePlayer->hand.back(), pair<int, int>(x, y));
cout << endl;
FieldPrint(g->field);
cout << endl;
g->makeTurn();

}
catch (BuildError &e)
{

}
}

}
catch (GameOver& e)
{
cout << e.getWinner().getName() << " WIN!!!" << endl;
}

string s;
cin >> s;

return 0;
}
*/