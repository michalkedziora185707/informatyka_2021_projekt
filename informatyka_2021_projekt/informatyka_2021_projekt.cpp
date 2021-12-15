#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>
using namespace std;
using namespace sf;
class enemy{
private:

	CircleShape * gw;
	int N;

	std::random_device rd;

public:
   enemy(int Nt);
	void draw(sf::RenderWindow& window);
	void move();
};


enemy::enemy(int Nt) {

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, 800);
	std::uniform_int_distribution<> distY(1, 600);
	std::uniform_int_distribution<> distR(1, 10);
	std::uniform_int_distribution<> distGreen(1, 50);
	std::uniform_int_distribution<> distRed(1, 50);
	float x = 0, y = 0;

	N = Nt;
	gw = new sf::CircleShape[N];
	for (int i = 0; i < N; i++)
	{
		x = distX(gen);
		y = distY(gen);
		gw[i].setPosition(Vector2f(x, y));
		gw[i].setRadius(distR(gen));
		gw[i].setFillColor(Color(190 + distRed(gen), 190 + distGreen(gen), 200));



	}
}

void enemy::draw(sf::RenderWindow& window) {
	for (int i = 0; i < N; i++)
	{
		window.draw(gw[i]);
	}
}

void enemy::move() {
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, 800);
	std::uniform_int_distribution<> distY(1, 600);
	std::uniform_int_distribution<> distXl(-10, 10);
	std::uniform_int_distribution<> distYl(-10, 10);
	for (int i = 0; i < N; i++)
	{
		gw[i].move(sf::Vector2f(distXl(gen), distYl(gen)));
		sf::Vector2f position = gw[i].getPosition();
		if (position.x > 750 || position.x < 0 || position.y > 530 || position.y < 0)
			gw[i].setPosition(distX(gen), distY(gen));
	}

}

class player {
private:
	Vector2f pos;
	CircleShape postac;
public:
	player(float x_in, float y_in);
	void przesun(float x_in, float y_in);
	CircleShape getpostac() { return postac; }
	Vector2f getPos() { return postac.getPosition(); }


};
player::player(float x_in, float y_in)
{
	pos.x = x_in;
	pos.y = y_in;
	postac.setRadius(20);
		postac.setFillColor(sf::Color(150, 50, 250));
		// obramowka kola o grubosci 2px
		postac.setOutlineThickness(2);
		postac.setOutlineColor(sf::Color(250, 150, 100));
		postac.setPosition(pos);//pozycja poczatkowa
	
	/*Texture textura;
	textura.loadFromFile("kot3.jpg");
	IntRect kszalt(0, 0, 150, 100);
	Sprite postac(textura, kszalt);
	postac.setPosition(pos);*/
}

void player::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	postac.move(pos);
}

class Menu
{

private:
	sf::Font font;
	sf::Text menu[4];
	int selectedItem = 0;


public:
	Menu(float width, float height);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
};


Menu::Menu(float width, float height){

	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	
	menu[0].setFont(font);	
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (4 + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Ostatnie wyniki");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (4 + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (4 + 1) * 3));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Zasady gry");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (4 + 1) * 4));
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < 4)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem =4 - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
	
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < 4)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= 4)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
}


void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
			
	}	
}


int main()
{
	Clock zegar;
	enemy gw(10);
	/*Texture textura;
	textura.loadFromFile("kot3.jpg");
	IntRect kszalt(0,0,150, 100);

	Sprite postac(textura, kszalt);
	
	postac.setPosition(200, 200);*/
	
	player p1(200, 200);
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "gierka");
	Menu menu(window.getSize().x, window.getSize().y);
	
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(250);
					menu.przesunG();
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(250);
					menu.przesunD();
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						cout << "Uruchamiam gre..." << std::endl;
						while (window.isOpen())
						{
							sf::Event event;
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::A))
							{
								p1.przesun(-0.2, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::D))
							{
								p1.przesun(0.2, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::W))
							{
								p1.przesun(0, -0.2);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::S))
							{
								p1.przesun(0, 0.2);
							}
							if (zegar.getElapsedTime().asMilliseconds() > 100.0f) {
								gw.move();
								zegar.restart();
							}

							window.clear();
							gw.draw(window);
							
							window.draw(p1.getpostac());

							window.display();

							menu_selected_flag = 1;
						}

						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
						{
							cout << "Najlepsze wyniki..." << std::endl;
							menu_selected_flag = 1;
						}

						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
						{
							cout << "Koniec gry..." << std::endl;
							menu_selected_flag = 1;
							return 0;
						}
						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
						{
							cout << "Koniec gry..." << std::endl;
							menu_selected_flag = 1;
						}

					}


				}
			}

		}


			window.clear();
			if (menu_selected_flag == 0)
				menu.draw(window);
			window.display();



		}
	}



