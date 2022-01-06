#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cmath>
using namespace std;
using namespace sf;
class zdrowie {
private:

	CircleShape* zdr;
	int N;

	random_device rd;

public:
	zdrowie(int Nt);
	void draw(sf::RenderWindow& window);
	void move();
	FloatRect getBounds() { return zdr->getGlobalBounds(); }
	Vector2f  getPos1(int i) { return zdr[i].getPosition(); }
	void przesun1(float x_in, float y_in, int i);
	int getSize() { return N; }
	Texture zdrowie_t;
};


zdrowie::zdrowie(int Nt) {

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(15, 1185);
	

	float x = 0, y = 0;

	N = Nt;
	zdr = new sf::CircleShape[N];
	for (int i = 0; i < N; i++)
	{
		x = distX(gen);
		y = 1;

		zdr[i].setPosition(Vector2f(x, y));
		zdr[i].setRadius(15);
		zdr[i].setFillColor(Color::White);

		zdrowie_t.loadFromFile("zdrowie.png");
		zdr[i].setTexture(&zdrowie_t);

	}
}
void zdrowie::przesun1(float x_in, float y_in, int i)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	zdr[i].move(pos);
}
void zdrowie::draw(sf::RenderWindow& window) {
	for (int i = 0; i < N; i++)
	{
		window.draw(zdr[i]);
	}
}void zdrowie::move() {
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(15, 1185);
	std::uniform_int_distribution<> distY(1, 600);
	std::uniform_int_distribution<> distXl(-30, 30);
	std::uniform_int_distribution<> distYl(-30, 30);
	for (int i = 0; i < N; i++)
	{
		zdr[i].move(sf::Vector2f(0, 2));
		sf::Vector2f position = zdr[i].getPosition();
		if ( position.y > 2000 || position.y < 0)
			zdr[i].setPosition(distX(gen), 0);
	}

}

class enemy {
private:

	CircleShape* gw;
	int N;

	random_device rd;

public:
	enemy(int Nt);
	void draw(sf::RenderWindow& window);
	void move();
	FloatRect getBounds() { return gw->getGlobalBounds(); }
	Vector2f  getPos1(int i) { return gw[i].getPosition(); }
	void przesun1(float x_in, float y_in, int i);
	int getSize() { return N; }
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
void enemy::przesun1(float x_in, float y_in, int i )
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	gw[i].move(pos);
}
void enemy::draw(sf::RenderWindow& window) {
	for (int i = 0; i < N; i++)
	{
		window.draw(gw[i]);
	}
}

void enemy::move() {
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(15, 1185);
	std::uniform_int_distribution<> distY(1, 600);
	std::uniform_int_distribution<> distXl(-30, 30);
	std::uniform_int_distribution<> distYl(-30, 30);
	for (int i = 0; i < N; i++)
	{
		gw[i].move(sf::Vector2f(0,1));
		sf::Vector2f position = gw[i].getPosition();
		if (position.x > 1200 || position.x < 0 || position.y > 800|| position.y < 0)
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
}

void player::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	postac.move(pos);
}

 class interfejs {
protected:
	sf::Vector2f bounds;
	sf::Vector2f innerBounds;
	sf::Text* goraLewy;
	sf::Text* goraPrawy;
	sf::Text* dol;
	Text* kontynuacja;
	sf::Font* czcionka;
	void init();

public:
	interfejs(sf::Vector2f _bounds);
	interfejs();
	void draw(sf::RenderWindow& okno);
	void update(std::string _goraLewy, std::string _goraPrawy, std::string _dol, string _kontynuacja);
};


void interfejs::init() {
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;

	goraLewy = new sf::Text;
	goraPrawy = new sf::Text;
	dol = new sf::Text;
	kontynuacja = new Text;

	goraLewy->setFont(*czcionka);
	goraLewy->setCharacterSize(22);
	goraLewy->setPosition(10, 5);
	goraLewy->setFillColor(sf::Color::Cyan);
	goraLewy->setString("Left top");


	goraPrawy->setFont(*czcionka);
	goraPrawy->setCharacterSize(22);
	goraPrawy->setPosition(1000,5);
	goraPrawy->setFillColor(sf::Color::Red);
	goraPrawy->setString("Right top");

	dol->setFont(*czcionka);
	dol->setCharacterSize(18);
	dol->setPosition(10,770);
	dol->setFillColor(sf::Color::Black);
	dol->setString("Center bot");

	kontynuacja->setFont(*czcionka);
	kontynuacja->setCharacterSize(18);
	kontynuacja->setPosition(600, 400);
	kontynuacja->setFillColor(sf::Color::Black);
	kontynuacja->setString("kont");

	//help1->setFont(*czcionka);
	//help1->setCharacterSize(12);
	//help1->setPosition(500, 300);
	//help1->setFillColor(sf::Color::Black);
	//help1->setString("info1");

	//help2->setFont(*czcionka);
	//help2->setCharacterSize(12);
	//help2->setPosition(500, 320);
	//help2->setFillColor(sf::Color::Black);
	//help2->setString("info2");

	/*obszar->setPosition(470, 280);
	obszar->setSize(Vector2f(500,50));
	obszar->setFillColor(sf::Color::Blue);*/
	innerBounds.x = bounds.x - 45;
	innerBounds.y = bounds.y - 80;
}


void interfejs::update(std::string _goraLewy, std::string _goraPrawy, std::string _dol, string _kontynuacja) {
	goraLewy->setString(_goraLewy);
	goraPrawy->setString(_goraPrawy);
	dol->setString(_dol);
	kontynuacja->setString(_kontynuacja);

}


interfejs::interfejs(sf::Vector2f _bounds) :bounds(_bounds) {
	this->init();
}

interfejs::interfejs() {
	this->bounds.x = 800.0;
	this->bounds.y = 600.0;
	this->init();
}
class interfejsTekst :public interfejs {

private:
	sf::Text* glownyTekst;

public:
	interfejsTekst(sf::Vector2f _bounds);
	void draw(sf::RenderWindow& okno);
};


interfejsTekst::interfejsTekst(sf::Vector2f _bounds) {
	this->bounds = _bounds;
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;

	glownyTekst = new sf::Text;

	glownyTekst->setFont(*czcionka);
	glownyTekst->setCharacterSize(28);
	glownyTekst->setPosition(25, 60);
	glownyTekst->setFillColor(sf::Color::Red);
	

}

void interfejsTekst::draw(sf::RenderWindow& okno) {
	interfejs::draw(okno);
	okno.draw(*glownyTekst);
}

void interfejs::draw(sf::RenderWindow& okno) {
	okno.draw(*goraLewy);
	okno.draw(*goraPrawy);
	okno.draw(*dol);

	//okno.draw(*kontynuacja);
}
class gameOver :public sf::Text {
private:
	sf::Font czcionka;

public:
	gameOver() {
		if (!czcionka.loadFromFile("arial.ttf"))
			return;

		this->setFont(czcionka);
		this->setCharacterSize(68);
		this->setPosition(300, 120);
		this->setFillColor(sf::Color::Cyan);
		this->rotate(45);
		this->setString("Game Over :)");

	}

};
class help :public sf::Text{
private:
	sf::Font czcionka;

public:
	help() {
		if (!czcionka.loadFromFile("arial.ttf"))
			return;

		this->setFont(czcionka);
		this->setCharacterSize(15);
		this->setPosition(440, 300);
		this->setFillColor(sf::Color::White);
		this->setString("Zasady gry: eliminuj przeciwnikow, zdobywaj punkty zdrowia");
	}
};
class help2 :public sf::Text {
private:
	sf::Font czcionka;
public:
	help2() {
		if (!czcionka.loadFromFile("arial.ttf"))
			return;

		this->setFont(czcionka);
		this->setCharacterSize(15);
		this->setPosition(400, 320);
		this->setFillColor(sf::Color::White);
		this->setString("Sterowanie: W-ruch w gore, S-ruch w dol, A-ruch w lewo, D-ruch w prawo");
	}
};
class obszar :public sf::RectangleShape {
private:
	sf::Font czcionka;
public:
	obszar() {
		if (!czcionka.loadFromFile("arial.ttf"))
			return;

		this->setSize(Vector2f(550,60));
		this->setPosition(375, 290);
		this->setFillColor(sf::Color::Black);
	}
};
class konty :public sf::Text {
private:
	sf::Font czcionka;

public:
	konty() {
		if (!czcionka.loadFromFile("arial.ttf"))
			return;

		this->setFont(czcionka);
		this->setCharacterSize(30);
		this->setPosition(400, 600);
		this->setFillColor(sf::Color::White);
		this->setString("Czy chcesz kontynuowac?");
	}

};

class Menu
{

private:
	sf::Font font;
	sf::Text menu[6];
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
	menu[0].setString("Poziom 1 (latwy)");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Poziom 2 (sredni)");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Poziom 3 (trudny)");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 3));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Zasady gry");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 4));
	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("Ostatnie wyniki");
	menu[4].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 5));
	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::White);
	menu[5].setString("Wyjscie z gry");
	menu[5].setPosition(sf::Vector2f(width / 3, height / (6 + 1) * 6));
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 6; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < 6)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem =6 - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
	
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < 6)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= 6)
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
powrot:;
	Clock zegar;
	interfejsTekst* IT1 = new interfejsTekst(sf::Vector2f(640.0, 480.0));
	gameOver* GO = new gameOver;
	help* help1 = new help;
	help2* help3 = new help2;
	obszar* obszar1 = new obszar;
	konty* kontynuacja = new konty;
	zdrowie zdr(1);
	RectangleShape podloga(Vector2f(1200, 50));
	podloga.setPosition(0, 750);
	podloga.setFillColor(Color::Green);
	FloatRect podlogab = podloga.getGlobalBounds();
	int scores = 0;
	int life = 5;
	int wybor = 0;
	player p1(200, 200);
	FloatRect pb = p1.getBounds();
	RectangleShape tlo(Vector2f(1200, 800));
	tlo.setPosition(0, 0);
	Texture tlo_t;
	tlo_t.loadFromFile("tlo1.png");
	tlo.setTexture(&tlo_t);
	RectangleShape tlo2(Vector2f(1200, 800));
	tlo2.setPosition(0, 0);
	Texture tlo_t2;
	tlo_t2.loadFromFile("tlo2.jpg");
	tlo2.setTexture(&tlo_t2);
	RectangleShape tlo3(Vector2f(1200, 800));
	tlo3.setPosition(0, 0);
	Texture tlo_t3;
	tlo_t3.loadFromFile("tlo3.jpg");
	tlo3.setTexture(&tlo_t3);
	int menu_selected_flag = 0;
	int a = 0;
	RenderWindow window(sf::VideoMode(1200, 800), "gierka");
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

						enemy gw(4);
						while (window.isOpen())
						{
							sf::Event event;


							FloatRect gwb = gw.getBounds();
							FloatRect zdrb = zdr.getBounds();
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
							}

							if (Keyboard::isKeyPressed(Keyboard::Key::A))
							{
								p1.przesun(-0.25, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::D))
							{
								p1.przesun(0.25, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::W))
							{
								p1.przesun(0, -0.25);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::S))
							{
								p1.przesun(0, 0.25);
							}

							if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
								gw.move();
								zdr.move();
								zegar.restart();
							}
							for (int i = 0; i < gw.getSize(); i++) {

								float dx = ((p1.getPos().x + (pb.width / 2)) - (gw.getPos1(i).x + (gwb.width / 2)));
								float dy = ((p1.getPos().y + (pb.height / 2)) - (gw.getPos1(i).y + (gwb.height / 2)));
								float distance = sqrt((dx * dx) + (dy * dy));
								if (distance <= ((pb.width / 2) + (gwb.width / 2)))
								{
									gw.przesun1(1300, 0, i);
									scores++;
									cout << scores;

								}
								for (int i = 0; i < zdr.getSize(); i++) {

									float dx = ((p1.getPos().x + (pb.width / 2)) - (zdr.getPos1(i).x + (zdrb.width / 2)));
									float dy = ((p1.getPos().y + (pb.height / 2)) - (zdr.getPos1(i).y + (zdrb.height / 2)));
									float distance = sqrt((dx * dx) + (dy * dy));
									if (distance <= ((pb.width / 2) + (zdrb.width / 2)))
									{
										zdr.przesun1(1300, 0, i);
										life++;
										cout << life;

									}
								}

							}
							for (int i = 0; i < gw.getSize(); i++) {
								if (gw.getPos1(i).y == 735)
								{
									life--;

									gw.przesun1(1300, 0, i);
									cout << life;
								}
							}



							window.clear();
							window.draw(tlo);
							window.draw(podloga);

							IT1->update("Scores: " + std::to_string(scores), "Punkty zycia: " + std::to_string(life), "level: 1", "Czy chcesz kontynuowac ? ");

							IT1->draw(window);
							if (life <= 0)
							{
								window.draw(*GO);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::F2))
							{
								goto powrot;
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::F1))
							{
								zegar.getElapsedTime().asMilliseconds() == 5.0f;
								
								window.draw(*obszar1);
								window.draw(*help1);
								window.draw(*help3);
								
								
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								//window.draw(*kontynuacja);
									//window.display();
									//Sleep(2000);
							}
							gw.draw(window);
							zdr.draw(window);
							//oknoGlowne->draw(window);
							window.draw(p1.getpostac());

							window.display();

							menu_selected_flag = 1;
						}
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						enemy gw(6);
						while (window.isOpen())
						{
							sf::Event event;

							FloatRect gwb = gw.getBounds();
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
							}

							if (Keyboard::isKeyPressed(Keyboard::Key::A))
							{
								p1.przesun(-0.3, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::D))
							{
								p1.przesun(0.3, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::W))
							{
								p1.przesun(0, -0.3);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::S))
							{
								p1.przesun(0, 0.3);
							}
							if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
								gw.move();

								zegar.restart();
							}
							for (int i = 0; i < gw.getSize(); i++) {

								float dx = ((p1.getPos().x + (pb.width / 2)) - (gw.getPos1(i).x + (gwb.width / 2)));
								float dy = ((p1.getPos().y + (pb.height / 2)) - (gw.getPos1(i).y + (gwb.height / 2)));
								float distance = sqrt((dx * dx) + (dy * dy));
								if (distance <= ((pb.width / 2) + (gwb.width / 2)))
								{
									gw.przesun1(1300, 0, i);
									scores++;
									cout << scores;

								}

							}
							for (int i = 0; i < gw.getSize(); i++) {
								if (gw.getPos1(i).y + 15 == 730)
								{
									life--;

									gw.przesun1(1300, 0, i);
									cout << life;
								}
							}



							window.clear();
							window.draw(tlo2);
							window.draw(podloga);
							if (Keyboard::isKeyPressed(Keyboard::Key::F2))
							{
								goto powrot;
							}
							IT1->update("Scores: " + std::to_string(scores), "Punkty zycia: " + std::to_string(life), "level: 1", "Czy chcesz kontynuowac? 1. tak   2. nie");

							IT1->draw(window);
							if (life <= 0)
							{
								window.draw(*GO);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))

							{
								window.draw(*kontynuacja);
								window.display();
								Sleep(3000);
								cin >> wybor;

								if (wybor == 1)
								{

								}
								if (wybor == 2)
								{
									return 0;
								}

							}
							gw.draw(window);
							window.draw(p1.getpostac());

							window.display();

							menu_selected_flag = 1;
						}
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{

						enemy gw(3);
						while (window.isOpen())
						{
							sf::Event event;

							FloatRect gwb = gw.getBounds();
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
							}

							if (Keyboard::isKeyPressed(Keyboard::Key::A))
							{
								p1.przesun(-0.3, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::D))
							{
								p1.przesun(0.3, 0);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::W))
							{
								p1.przesun(0, -0.3);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::S))
							{
								p1.przesun(0, 0.3);
							}
							if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {
								gw.move();

								zegar.restart();
							}
							
							for (int i = 0; i < gw.getSize(); i++) {

								float dx = ((p1.getPos().x + (pb.width / 2)) - (gw.getPos1(i).x + (gwb.width / 2)));
								float dy = ((p1.getPos().y + (pb.height / 2)) - (gw.getPos1(i).y + (gwb.height / 2)));
								float distance = sqrt((dx * dx) + (dy * dy));
								if (distance <= ((pb.width / 2) + (gwb.width / 2)))
								{
									gw.przesun1(1300, 0, i);
									scores++;
									cout << scores;
								}
							}
								for (int i = 0; i < gw.getSize(); i++) {
									if (gw.getPos1(i).y + 15 == 730)
									{
										life--;

										gw.przesun1(1300, 0, i);
										cout << life;
									}
								}

								if (Keyboard::isKeyPressed(Keyboard::Key::F2))
								{
									goto powrot;
								}

								window.clear();
								window.draw(tlo3);
								window.draw(podloga);
								if (Keyboard::isKeyPressed(Keyboard::Key::F2))
								{
									goto powrot;
								}
								IT1->update("Scores: " + std::to_string(scores), "Punkty zycia: " + std::to_string(life), "level: 1", "Czy chcesz kontynuowac? 1. tak   2. nie");

								IT1->draw(window);
								if (life <= 0)
								{
									window.draw(*GO);
								}
								gw.draw(window);
								window.draw(p1.getpostac());

								window.display();

								menu_selected_flag = 1;
							

						}
						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
						{
							cout << "Zasady gry:" << endl;
							cout << "Twoim zadaniem jest zabijanie przeciwnikow lecacych z gory ekranu." << endl;
							cout << "Nie mozesz dopuscic aby wrogowie dotarli na dol ekranu." << endl;
							cout << "W tym celu musisz za pomoca klawiszy WSAD najezdzac na wrogow." << endl;
							cout << "Na start dostajesz 5 zyc, kazdy wrog ktory odjdzie do konca odejmuje Ci jedno zycie." << endl;
							cout << "Dodatkowo co pewien czas przez ekran przelatuje 1pkt zycia, ktory rowniez mozesz zdobyc." << endl;
							cout << "Za kazdego zabitego wroga dostajesz punkt, im wiecej punktow tym lepiej." << endl;
							cout << "Do wyboru masz 3 poziomy trudnosci, tylko uwazaj bo ostatni to nie lada wyzwanie." << endl;
							cout << "Sterowanie:" << endl;
							cout << "W - ruch gracza do gory" << endl;
							cout << "S - ruch gracza w dol" << endl;
							cout << "A - ruch gracza w lewo" << endl;
							cout << "D - ruch gracza w prawo" << endl;
							if (Keyboard::isKeyPressed(Keyboard::Key::F2))
							{
								goto powrot;
							}
							menu_selected_flag = 1;
						}
						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 4)
						{
							cout << "Ostatnie wyniki" << endl;
							menu_selected_flag = 1;
						}
						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 5)
						{
							cout << "Wyjscie z gry" << endl;
							return 0;
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

		return 0;
	}

	



