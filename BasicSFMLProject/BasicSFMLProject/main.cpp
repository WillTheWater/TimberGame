#include "SFML/Graphics.hpp"

int main()
{
	sf::VideoMode gameWindow(1920, 1080);
	sf::RenderWindow window(gameWindow, "Window");
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
		}
		window.clear(sf::Color(150, 150, 150, 255));
		window.display();
	}

	return 0;
}