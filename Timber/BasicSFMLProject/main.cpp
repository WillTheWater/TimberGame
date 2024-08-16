#include "SFML/Graphics.hpp"

int main()
{
	sf::VideoMode gameWindow(1920, 1080);
	sf::RenderWindow window(gameWindow, "Timber");
	sf::Event event;

	//----------Background------------
	sf::Texture textureBG;
	textureBG.loadFromFile("assets/graphics/background.png");
	sf::Sprite sprtieBG;
	sprtieBG.setTexture(textureBG);
	sprtieBG.setPosition(0, 0);
	//--------------------------------
	//----------Tree------------------
	sf::Texture textureTree;
	textureTree.loadFromFile("assets/graphics/tree.png");
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);
	//--------------------------------
	//------------Bee-----------------
	sf::Texture textureBee;
	textureBee.loadFromFile("assets/graphics/bee.png");
	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.f;
	//--------------------------------
	//----------Clouds----------------
	sf::Texture textureCloud;
	textureCloud.loadFromFile("assets/graphics/cloud.png");
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0.f;
	float cloud2Speed = 0.f;
	float cloud3Speed = 0.f;
	//-------------------------------
	//----------Clock----------------
	sf::Clock gameClock;
	

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
		}

		sf::Time deltaTime = gameClock.restart();

		window.clear(sf::Color(150, 150, 150, 255));
		window.draw(sprtieBG);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3); 
		window.draw(spriteTree);
		window.draw(spriteBee); 
		window.display();
	}

	return 0;
}