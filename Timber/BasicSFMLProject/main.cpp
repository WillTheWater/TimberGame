#include "SFML/Graphics.hpp"
#include <sstream>

void UpdateBranches(int seed);
const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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
	//----------Timebar--------------
	sf::RectangleShape timebar;
	float timeBarStartWidth = 400.f;
	float timeBarHeight = 80.f;
	timebar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timebar.setFillColor(sf::Color::Red);
	timebar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	sf::Time gameTimeToalt;
	float timeRemaining = 6.f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
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
	//--------------------------------
	//-----------Branches-------------
	sf::Texture textureBranch;
	textureBranch.loadFromFile("assets/graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}
	//--------------------------------
	//------------Player--------------
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("assets/graphics/player.png");
	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;
	//--------------------------------
	//----------Gravestone------------
	sf::Texture textureGrave;
	textureGrave.loadFromFile("assets/graphics/rip.png");
	sf::Sprite spriteGrave;
	spriteGrave.setTexture(textureGrave);
	spriteGrave.setPosition(600, 860);
	//--------------------------------
	//------------Axe-----------------
	sf::Texture textureAxe;
	textureAxe.loadFromFile("assets/graphics/axe.png");
	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	//--------------------------------
	//-------------Log----------------
	sf::Texture textureLog;
	textureLog.loadFromFile("assets/graphics/log.png");
	sf::Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	//-------------------------------

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { paused = false; score = 0; timeRemaining = 5; }
		}
		if (!paused)
		{
			
			sf::Time deltaTime = gameClock.restart();

			timeRemaining -= deltaTime.asSeconds();
			timebar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.f) 
			{ 
				paused = true; 
				messageText.setString("Out of Time!");
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
				messageText.setPosition(1920 / 2.f, 1080 / 2.f);
			}

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

			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else { branches[i].setPosition(3000, height); }
			}
		}
		window.clear(sf::Color(150, 150, 150, 255));
		window.draw(sprtieBG);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3); 
		for (int i = 0; i < NUM_BRANCHES; i++) { window.draw(branches[i]); }
		window.draw(spriteTree);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteGrave);
		window.draw(spriteBee); 
		window.draw(scoreText);
		window.draw(timebar);
		if (paused) { window.draw(messageText); }
		window.display();
	}

	return 0;
}

void UpdateBranches(int seed)
{
	for (int j = NUM_BRANCHES - 1; j > 0; j--) { branchPositions[j] = branchPositions[j - 1]; }
	std::srand((int)time(0) + seed);
	int randomInt = (rand() % 5);
	switch (randomInt)
	{
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
}