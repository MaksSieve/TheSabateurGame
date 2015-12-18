#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace std;
using namespace sf;

Font font;//Шрифт программы, инициализируется в main()
bool menuison;
int pnum;//Количество игроков
Game* g;//Основная игра

void drawmenu(RenderWindow&);//Функция отрисовки меню
void drawmap(Game*, Sprite, RenderWindow&);//Функция отрисовки карты
void mypause(Clock);//Пауза игры

int main()
{
	font.loadFromFile("arial.ttf");
	Clock clock;

	RenderWindow window(VideoMode(32*9, 32*9+50), "The Saboteur");//Основное окно игры
	Image mymap;
	mymap.loadFromFile("map.png");
	Texture mmap;
	mmap.loadFromImage(mymap);
	Sprite s_map;//Спрайт карты, создаваемый из текстуры из изображения
	s_map.setTexture(mmap);
	Text text("", font, 20);//Выыводимый текст
	text.setColor(Color::Red);
	text.setPosition(0, window.getSize().y - 50);
	Text text2("", font, 20);
	text2.setColor(Color::Red);
	text2.setPosition(0, 0);
	pnum = 0;//Инициализируем количество игроков
	Player* tmp;
	//string tmp_s[2] = { "dm", "mks" };//Пассивно созданный массив с игроками
	//for (int i = 0; i < pnum; i++) 
	//{
	//	tmp = new Player();
	//	tmp->setName(tmp_s[i]);
	//	g->players.push_back(tmp);
	//}
	//g->start();
	string name;//Строка ввода
	bool infonotentered=1;//Переменная ввода данных игроков
	int plnum = 0;
	menuison = true;
	while (window.isOpen())//Основной цикл приложения
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)//Условие для ввода текста
			{
				if (48<= event.text.unicode && event.text.unicode < 57 || 65 <= event.text.unicode && event.text.unicode < 90 || 97 <= event.text.unicode && event.text.unicode < 122)
					name+= static_cast<char>(event.text.unicode);
				if (event.text.unicode==8 && name.length()>0) {//Обработка Backspace
					name.erase(name.length()-1,1);
				}
			}
		}
		window.clear();
		drawmenu(window);
		if (infonotentered) 
		{//Ввод данных игроков
			if (plnum)
				text2.setString("Enter player " + to_string(plnum) + " name: " + name);
			else
				text2.setString("Enter number of players: " + name);
			window.draw(text2);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Return)) //Вход в условие по Enter
			{
				mypause(clock);
				switch (plnum) 
				{
				case 0: {
					pnum = stoi(name);				
					plnum++;
					name = "";	
					g = new Game(pnum);//Создание игры
					break;
				}
				default:
				{
					tmp = new Player();//Создание и присваивание игре нового
					tmp->setName(name);
					g->players.push_back(tmp);
					plnum++;
					name = "";
					break;
				}
				}
				if (plnum - 1 == pnum)
				{
					infonotentered = 0;//Данные введены
					g->start();//Начало игры
				}
				mypause(clock);
			}
		}
		else
		{
			drawmap(g, s_map, window);
			text.setString("Current Player: " + g->activePlayer->getName());
			window.draw(text);
			Vector2i pos = Mouse::getPosition(window);
			if (Mouse::isButtonPressed(Mouse::Left) && pos.x>=0 && pos.x<=window.getSize().x&&pos.y>0&& pos.y <= window.getSize().y-50)
			{//Обработка нажатия на карту
				try
				{
					//while (!g->deck.empty()) //Задел на будущее
					//{
					try
					{//Построение туннеля активным игроком и переход к новому игроку
						g->buildTunnel(g->activePlayer->hand.back(), pair<int, int>((pos.x) / 32 + 1, (pos.y) / 32 + 1));
						g->makeTurn();
					}
					catch (BuildError &e)
					{

					}

					//}

				}
				catch (GameOver& e)//Исключение конца игры
				{
					text.setString(e.getWinner()->getName() + " WIN!!!\nPress space to exit.");
					window.clear();
					drawmap(g, s_map, window);
					window.draw(text);
					window.display();
					clock.restart();
					menuison = true;
					while (menuison)//Ждём пока пользователь осознает своё счастье
					{
						if (Keyboard::isKeyPressed(Keyboard::Space))
							break;
					}
					infonotentered = 1;//Удаляем игру, данные игроков и их количество
					delete g;
					plnum = 0;
 					continue;
				}
			}
			window.display();
			mypause(clock);
		}
	}
	return 0;
}

void drawmenu(RenderWindow& window)//Отрисовка меню
{
	while (menuison)
	{
		Clock clock;
		window.clear();
		Text text("Start game", font, 20);//Текстики в главном окне
		Text text1("Leaderboard", font, 20);
		Text text2("Exit", font, 20);
		text.setColor(Color::Red);
		text1.setColor(Color::Red);
		text2.setColor(Color::Red);
		text.setPosition(window.getSize().x/6, window.getSize().y / 6);
		text1.setPosition(window.getSize().x / 6, window.getSize().x /2);
		text2.setPosition(window.getSize().x / 6, window.getSize().x*4 / 6);
		window.draw(text);
		//window.draw(text1);
		window.draw(text2);
		window.display();
		mypause(clock);
		Vector2i* pos =new Vector2i(Mouse::getPosition(window));//Опять получение клика в окне
		if (Mouse::isButtonPressed(Mouse::Left) && (*pos).x >= window.getSize().x / 6 && (*pos).x <= window.getSize().x*5/6)
		{
			if ((*pos).y>= window.getSize().y / 6 && (*pos).y<= window.getSize().y *2/ 6) 
			{
				//Кликнули на первую строку
				menuison = 0;
				continue;
			}
			if ((*pos).y >= window.getSize().x * 4 / 6 && (*pos).y <= window.getSize().y * 5 / 6)
			{
				//И на вторую
				exit(0);
			}
		}
	}
}

void mypause(Clock clock)//Пауза
{
	clock.restart();
	while (clock.getElapsedTime().asSeconds() <= 0.08)
	{

	}
}

void drawmap(Game* g, Sprite s_map, RenderWindow& window)//Отрисовка карты
{
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j <9; j++) 
		{
			Card* cell = g->field[i + 1][j + 1];//Выводим карту в качесве массива
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