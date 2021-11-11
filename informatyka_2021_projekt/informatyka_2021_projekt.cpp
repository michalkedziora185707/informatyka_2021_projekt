#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(20);
	shape.setFillColor(sf::Color::Green);

	RectangleShape proba(Vector2f(300,600));
	proba.setPosition(0, 0);
	proba.setFillColor(Color::Blue);
	RectangleShape proba1(Vector2f(500, 200));
	proba1.setPosition(300, 0);
	proba1.setFillColor(Color::Blue);
	RectangleShape proba2(Vector2f(200, 200));
	proba2.setPosition(, 0);
	proba2.setFillColor(Color::Blue);

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.draw(proba);
		window.draw(proba1);
		//window.draw(proba3);
		window.display();
		
	}
	return 0;
}



