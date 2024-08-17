#include "SFML/Graphics.hpp"
#include <sstream>

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
	//-----------Clock---------------
	sf::Clock gameClock;
	//-------------------------------
	//-----------Pause---------------
	bool paused = true;
	//-------------------------------
	//-----------Text----------------
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;
	sf::Font font;
	font.loadFromFile("assets/fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter to Start");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);
	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	messageText.setPosition(1920 / 2.f, 1080 / 2.f);
	scoreText.setPosition(20, 20);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { paused = false; }
		}
		if (!paused)
		{
			
			sf::Time deltaTime = gameClock.restart();

			if (!beeActive)
			{
				std::srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 100;
				std::srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * deltaTime.asSeconds()), spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < -100) { beeActive = false; }
			}

			if (!cloud1Active)
			{
				std::srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
				std::srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-400, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * deltaTime.asSeconds()), spriteCloud1.getPosition().y);
				if (spriteCloud1.getPosition().x > 1920) { cloud1Active = false; }
			}

			if (!cloud2Active)
			{
				std::srand((int)time(0) * 15);
				cloud2Speed = (rand() % 200);
				std::srand((int)time(0) * 10);
				float height = (rand() % 300);
				spriteCloud2.setPosition(-400, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * deltaTime.asSeconds()), spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x > 1920) { cloud2Active = false; }
			}

			if (!cloud3Active)
			{
				std::srand((int)time(0) * 20);
				cloud3Speed = (rand() % 200);
				std::srand((int)time(0) * 10);
				float height = (rand() % 500);
				spriteCloud3.setPosition(-400, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * deltaTime.asSeconds()), spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 1920) { cloud3Active = false; }
			}
			std::stringstream streamScore;
			streamScore << "Score = " << score;
			scoreText.setString(streamScore.str());
		}
		window.clear(sf::Color(150, 150, 150, 255));
		window.draw(sprtieBG);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3); 
		window.draw(spriteTree);
		window.draw(spriteBee); 
		window.draw(scoreText);
		if (paused) { window.draw(messageText); }
		window.display();
	}

	return 0;
}