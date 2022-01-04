#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <vector>
//#include <cmath>
//#include <Windows.h>
using namespace std;
using namespace sf;

class enemy{
private:

	CircleShape  *gw;
	int N;
	
	random_device rd;

public:
   enemy(int Nt);
	void draw(sf::RenderWindow& window);
	void move();
	FloatRect getBounds() { return gw->getGlobalBounds(); }
	Vector2f getPos1() { return gw->getPosition(); }
	void przesun1(float x_in, float y_in);
	Texture enemy1;
};


enemy::enemy(int Nt) {

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, 800);
	std::uniform_int_distribution<> distY(1, 600);

	float x = 0, y = 0;

	N = Nt;
	gw = new sf::CircleShape[N];
	for (int i = 0; i < N; i++)
	{
		x = distX(gen);
		y = distY(gen);
		
		gw[i].setPosition(Vector2f(x, y));
		gw[i].setRadius(15);
		gw[i].setFillColor(Color::White);

		enemy1.loadFromFile("enemy.png");
		gw[i].setTexture(&enemy1);

	}
}
void enemy::przesun1(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	gw->move(pos);
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
	std::uniform_int_distribution<> distXl(-30, 30);
	std::uniform_int_distribution<> distYl(-30, 30);
	for (int i = 0; i < N; i++)
	{
		gw[i].move(sf::Vector2f(0,1));
		sf::Vector2f position = gw[i].getPosition();
		if (position.x > 800 || position.x < 0 || position.y > 600|| position.y < 0)
			gw[i].setPosition(distX(gen),0);
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
	FloatRect getBounds() { return postac.getGlobalBounds(); }

};
player::player(float x_in, float y_in)
{
	pos.x = x_in;
	pos.y = y_in;
	postac.setRadius(20);
		postac.setFillColor(sf::Color(150, 50, 250));
		postac.setOutlineThickness(2);
		postac.setOutlineColor(sf::Color(250, 150, 100));
		postac.setPosition(pos);
	
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


//class interfejs {
//protected:
//	Vector2f bounds;
//	Vector2f innerBounds;
//	Text* goraLewy;
//	Font* czcionka;
//	void init();
//	Font* czcionka1;
//public:
//	interfejs(sf::Vector2f _bounds);
//	interfejs();
//	void draw(sf::RenderWindow& okno);
//	void update(std::string _goraLewy);
//};
//void interfejs::init() {
//	
//
//	goraLewy = new sf::Text;
//	goraLewy->setFont(*czcionka);
//		goraLewy->setCharacterSize(18);
//		goraLewy->setPosition(10, 5);
//		goraLewy->setFillColor(sf::Color::Cyan);
//		goraLewy->setString("Left top");
//}
//void interfejs::update(std::string _goraLewy) {
//	goraLewy->setString(_goraLewy);
//}
//void interfejs::draw(sf::RenderWindow& okno) {
//	okno.draw(*goraLewy);
//}

int main()
{
	Clock zegar;
	int n = 10;
	enemy gw(1);
	RectangleShape podloga(Vector2f(800, 50));
	podloga.setPosition(0,550);
	podloga.setFillColor(Color::Green);
	
	
	/*Texture textura;
	textura.loadFromFile("kot3.jpg");
	IntRect kszalt(0,0,150, 100);

	Sprite postac(textura, kszalt);
	
	postac.setPosition(200, 200);*/
	
	player p1(200, 200);
	FloatRect pb = p1.getBounds();
	FloatRect gwb =gw.getBounds();
	
	int menu_selected_flag = 0;
	int a = 0;
	RenderWindow window(sf::VideoMode(800, 600), "gierka");
	//interfejs* oknoGlowne = new interfejs(sf::Vector2f(800.0, 600.0)); 
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
							if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
								gw.move();

								zegar.restart();
							}
							float dx = ((p1.getPos().x + (pb.width / 2)) - (gw.getPos1().x + (gwb.width / 2)));
							float dy = ((p1.getPos().y + (pb.height / 2)) - (gw.getPos1().y + (gwb.height / 2)));
							float distance = sqrt((dx * dx) + (dy * dy));
							for (int i = 0; i < 10; i++)
							{
								if (distance <= ((pb.width / 2) + (gwb.width / 2)))
								{
									gw.przesun1(700, 0);
									
									//cout << "kolizja w chuj" << endl;
								}
							}


							
							//if (p1.getPos().x+100 <= gw.getPos1().x +10 && p1.getPos().y+100  <= gw.getPos1().y+10 )
							//{
							//	
							//	//cout << "KOLIZJA!!!" << endl;
							//	
							//	gw.przesun1(1000, 0);
							//}
				
							//if (pb.intersects(gw.getBounds()))
							//{
							//	//cout << "kolizja" << endl;
							//	gw.przesun1(500, 0);
							//}
							//if (gw.getPos1().y >= 400)
							//{
							//	//cout << "smierc" << endl;
							//	gw.przesun1(500, 0);
							//}
						
						

							window.clear();
							//window.draw(podloga);
							gw.draw(window);
							
							//oknoGlowne->draw(window);
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


// zad 1:

//class interfejs {
//protected:
//	sf::Vector2f bounds;
//	sf::Vector2f innerBounds;
//	sf::Text* goraLewy;
//	sf::Text* goraPrawy;
//	sf::Text* dol;
//	sf::RectangleShape* obszar;
//	sf::Font* czcionka;
//	void init();
//
//public:
//	interfejs(sf::Vector2f _bounds);
//	interfejs();
//	void draw(sf::RenderWindow& okno);
//	void update(std::string _goraLewy, std::string _goraPrawy, std::string _dol);
//
//
//
//
//};
//
//
//void interfejs::init() {
//	czcionka = new sf::Font;
//	if (!czcionka->loadFromFile("arial.ttf"))
//		return;
//
//	goraLewy = new sf::Text;
//	goraPrawy = new sf::Text;
//	dol = new sf::Text;
//	obszar = new sf::RectangleShape;
//
//	goraLewy->setFont(*czcionka);
//	goraLewy->setCharacterSize(18);
//	goraLewy->setPosition(10, 5);
//	goraLewy->setFillColor(sf::Color::Cyan);
//	goraLewy->setString("Left top");
//
//
//	goraPrawy->setFont(*czcionka);
//	goraPrawy->setCharacterSize(28);
//	goraPrawy->setPosition(bounds.x - 200, 5);
//	goraPrawy->setFillColor(sf::Color::White);
//	goraPrawy->setString("Right top");
//
//	dol->setFont(*czcionka);
//	dol->setCharacterSize(18);
//	dol->setPosition(bounds.x / 3, bounds.y - 30);
//	dol->setFillColor(sf::Color::Yellow);
//	dol->setString("Center bot");
//
//	innerBounds.x = bounds.x - 45;
//	innerBounds.y = bounds.y - 80;
//	obszar->setPosition(22, 50);
//	obszar->setSize(innerBounds);
//	obszar->setFillColor(sf::Color::Blue);
//
//
//
//
//
//}
//
//
//void interfejs::update(std::string _goraLewy, std::string _goraPrawy, std::string _dol) {
//	goraLewy->setString(_goraLewy);
//	goraPrawy->setString(_goraPrawy);
//	dol->setString(_dol);
//}
//
//
//interfejs::interfejs(sf::Vector2f _bounds) :bounds(_bounds) {
//	this->init();
//}
//
//interfejs::interfejs() {
//	this->bounds.x = 800.0;
//	this->bounds.y = 600.0;
//	this->init();
//}
//
//
//void interfejs::draw(sf::RenderWindow& okno) {
//	okno.draw(*goraLewy);
//	okno.draw(*goraPrawy);
//	okno.draw(*dol);
//	okno.draw(*obszar);
//}
//// zad 2:
//class interfejsTekst :public interfejs {
//
//private:
//	sf::Text* glownyTekst;
//
//public:
//	interfejsTekst(sf::Vector2f _bounds);
//	void draw(sf::RenderWindow& okno);
//};
//
//
//interfejsTekst::interfejsTekst(sf::Vector2f _bounds) {
//	this->bounds = _bounds;
//	czcionka = new sf::Font;
//	if (!czcionka->loadFromFile("arial.ttf"))
//		return;
//
//	glownyTekst = new sf::Text;
//
//	glownyTekst->setFont(*czcionka);
//	glownyTekst->setCharacterSize(28);
//	glownyTekst->setPosition(25, 60);
//	glownyTekst->setFillColor(sf::Color::Red);
//	glownyTekst->setString("Wstep\nRozwiniecie\nZakonczenie");
//
//}
//
//void interfejsTekst::draw(sf::RenderWindow& okno) {
//	interfejs::draw(okno);
//	okno.draw(*glownyTekst);
//}
//
////zadanie 3:
//class gameOver :public sf::Text {
//private:
//	sf::Font czcionka;
//
//public:
//	gameOver() {
//		if (!czcionka.loadFromFile("arial.ttf"))
//			return;
//
//		this->setFont(czcionka);
//		this->setCharacterSize(68);
//		this->setPosition(300, 120);
//		this->setFillColor(sf::Color::Cyan);
//		this->rotate(45);
//		this->setString("Game Over :)");
//	}
//
//};
//
//int main()
//{
//	int a = 0;
//	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
//	//interfejs* oknoGlowne = new interfejs(sf::Vector2f(800.0, 600.0)); // zad 1
//	interfejsTekst* IT1 = new interfejsTekst(sf::Vector2f(640.0, 480.0)); // zad 2
//	gameOver* GO = new gameOver; // zad 3
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		window.clear();
//		a = a + 10;
//		IT1->update("Scores: " + std::to_string(a), "Player", "level: 200"); // zad 1/2
//		//oknoGlowne->draw(window); // zad 1
//		IT1->draw(window); // zad 2
//		window.draw(*GO); // zad 3
//		window.display();
//	}
//	return 0;
//}

