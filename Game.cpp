#include "Game.h"
#include "menu.h"
#include<string>


Menu menu3(1080,720);

int Game::level = 0;
int Game::finalLevel = 3;

Game::Game() :window(VideoMode(1080, 720), "Asteroid")
{

}

Game::~Game()
{
	
}

void Game::run()
{
	init();
	Clock clock;
	while (window.isOpen())
	{
		if (!gameOver)
		{
			processEvent();
			Time dt = clock.restart();
			update(dt.asSeconds());
			render();
		}
		else if(gameOver&&!gameWon)
		{
			clearMemory();
			level = 0;
			gameOverScreen();
				

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}
		}
		else if(gameOver&&gameWon)
		{
			level = 0;
			gameWonScreen();
			clearMemory();

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}
		}
		
	}
}

void Game::init()
{
	backgoundTexture.loadFromFile("gamebackground.png");
	backgroundSprite.setTexture(backgoundTexture);
	player.init();

}

void Game::clearMemory()
{
	for (int k = 0; k < enemies.size(); k++)
	{
		Enemy* enemy = enemies[k];
		enemies.erase(enemies.begin() + k);
		delete(enemy);
	}
	for (int k = 0; k < bosses.size(); k++)
	{
		Boss* boss = bosses[k];
		bosses.erase(bosses.begin() + k);
		delete boss;
	}
	for (int k = 0; k < lasers.size(); k++)
	{
		Laser* laser = lasers[0];
		lasers.erase(lasers.begin()+k);
		delete laser;
	}
}

void Game::processEvent()
{
	
	Event event;
	 if (enemies.size() == 0&&level!=3)
	{
		 level++;
		spawnEnemies();
		
	}
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if(event.key.code == Keyboard::Up)
			{
				player.setMoving(true);
			}
			else if (event.key.code == Keyboard::Left)
			{
				player.setRotation(-1);
				
			}
			else if (event.key.code == Keyboard::Right)
			{
				player.setRotation(1);
			}
			if (event.key.code == Keyboard::Space&&lasers.size()==0)
			{
				//std::cout << lasers.size()<<std::endl;
				shoot();
				//std::cout << lasers.size() <<" "<<player.getSprite().getOrigin().x<<" "<< player.getSprite().getOrigin().y << std::endl;

			}

		}
		else if (event.type == Event::KeyReleased)
		{
			
			if (event.key.code == Keyboard::Left)
			{
				player.setRotation(0);
			}
			else if (event.key.code == Keyboard::Right)
			{
				player.setRotation(0);
			}
			else if (event.key.code == Keyboard::Up)
			{
				player.setMoving(false);
			}

		}

	}
}

void Game::update(float deltaTime)
{
	player.updatePlayer(deltaTime);
	//tracking asteroid can be targeted at last so if all other asteroid are destroyed we make 
	//tracking asteroid normalAsteroid
	if (level == finalLevel)
	{
		for (Boss* boss : bosses)
		{
			boss->update(deltaTime, player.getSprite().getPosition());
			boss->updateTimeCount(deltaTime);
			//To spawn asteroids after 5sec
			if (boss->getSpawnTime() <= boss->getTimeCount())
			{
				boss->setTimeCount(0);
				Enemy* enemy = new slingingAsteroid();
				enemy->setplayerPosition(player.getSprite().getPosition());
				enemy->setPosition(boss->getSprite().getPosition());
				enemy->init();
				enemies.push_back(enemy);
			}
		}
		
	}
		if (enemies.size() == 1)
		{
			enemies[0]->setAsteroidTpye(true);
		}
		for (Laser* laser : lasers)
		{
			laser->update(deltaTime);
			//To check if the laser is out of screen and destory if it is out of bound
			if (laser->getSprite().getPosition().x < 0 || laser->getSprite().getPosition().x > 1000 ||
				laser->getSprite().getPosition().y < 0 || laser->getSprite().getPosition().y > 720)
			{
				lasers.erase(lasers.begin());
				delete(laser);
			}
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy* enemy = enemies[i];
			enemy->update(deltaTime, player.getSprite().getPosition());
		}
		//Check collision between laser and asteroids
		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy* enemy = enemies[i];

			for (int j = 0; j < lasers.size(); j++)
			{
				Laser* laser = lasers[j];
				//Check colloision
				if (enemy->getAseroidType())
				{
					if (laser->getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds()))
					{
						lasers.erase(lasers.begin() + j);
						delete(laser);
						//Check the hitcount of enemy
						enemy->setHitcount(enemy->gethitCount() + 1);
						if (enemy->gethitCount() == enemy->getnoOfHitsRequired())
						{
							enemies.erase(enemies.begin() + i);
							delete(enemy);
						}
						if (enemy->getnoOfHitsRequired() == 3)
						{
							for (int k = 0; k < 2; k++)
							{
								Enemy* smallAsteroid = new SmallAsteroid();
								smallAsteroid->setPosition(enemy->getPosition());
								smallAsteroid->init();
								enemies.push_back(smallAsteroid);
							}
							enemies.erase(enemies.begin() + i);
							delete(enemy);
						}

					}
				}

			}
		}
		//Collision between laser and boss
		for (int i = 0; i < bosses.size(); i++)
		{
			Boss* boss = bosses[i];
			for (int j = 0; j < lasers.size(); j++)
			{
				Laser* laser = lasers[j];
				if (laser->getSprite().getGlobalBounds().intersects(boss->getSprite().getGlobalBounds()))
				{
					boss->setHitcount(boss->gethitCount() + 1);
					if (boss->gethitCount() == boss->getnoOfHitsRequired())
					{
						bosses.erase(bosses.begin() + i);
						delete(boss);
						gameWon = true;
						gameOver = true;
						//Clearing memory after  game
					}
					lasers.erase(lasers.begin() + j);
					delete(laser);
				}
			}
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy* enemy = enemies[i];
			if (enemy->getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
			{
				gameOver = true;
			}
		}
		for (int i = 0; i < bosses.size(); i++)
		{
			Boss* boss = bosses[i];
			if (boss->getSprite().getGlobalBounds().
				intersects(player.getSprite().getGlobalBounds()))
			{
				gameOver = true;
			}
		}
	
	
	
}

void Game::render()
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(player.getSprite());
	for (Laser *laser : lasers)
	{
		window.draw(laser->getSprite());
	}
	for (Enemy* enemy : enemies)
	{
		window.draw(enemy->getSprite());
	}
	for (Boss* boss : bosses)
	{
		window.draw(boss->getSprite());
	}
	
	window.display();
}

void Game::spawnEnemies()
{
	if (level == finalLevel)
	{
		///
		Boss* boss = new Boss();
		boss->init();
		bosses.push_back(boss);
		Enemy* enemy = new TrackingAsteroid();
		enemy->init();
		enemies.push_back(enemy);
	}
	else
	{
		Enemy* enemy;
		for (int i = 0; i <= level*2; i++)
		{
			enemy = chooseEnemy(i);
			enemy->init();
			enemies.push_back(enemy);
		}
		enemy = new TrackingAsteroid();
		enemy->init();
		enemies.push_back(enemy);
		///
		
	}
	
	
	
}

void Game::shoot()
{
		Laser* laser = new Laser();
		laser->init(player.getSprite().getPosition(),player.getSprite().getRotation());
		lasers.push_back(laser);
}

Enemy* Game::chooseEnemy(int i)
{
	if (i%3==0)
	{
		return new BigAsteroid();
	}
	else if(i%3 == 1)
	{
		return new SmallAsteroid();
	}
	return new MediumAsteroid();
	
}

void Game::gameWonScreen()
{
	RectangleShape rect;
	rect.setFillColor(Color::Black);
	rect.setSize(Vector2f(1080, 720));
	window.clear();
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("Debrosee-ALPnL.ttf"))
    {
        //handle error
    }

	text.setFont(font);
    text.setFillColor(sf::Color::Green);
    text.setString("Congrats!!\n YOU WON");
	text.setPosition(200,200);
	text.setCharacterSize(100);
	sf::Event event;
        
   
	while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
						case sf::Keyboard::Return:
                            window.close();
                            menu3.run();
                            break;

                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
   
	window.draw(rect);
	window.draw(text);
	window.display();
}

void Game::gameOverScreen()
{
	RectangleShape rect;
	rect.setFillColor(Color::Black);
	rect.setSize(Vector2f(1080, 720));
	window.clear();
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("Debrosee-ALPnL.ttf"))
    {
        //handle error
    }

	text.setFont(font);
    text.setFillColor(sf::Color::Green);
    text.setString("\t\t\t\t\t\t\t\tYou've Lost!!\n\n\n\t\t\t\t\tPress Enter to Play again ");
	text.setPosition(20,200);
	text.setCharacterSize(50);



	sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
						case sf::Keyboard::Return:
                            window.close();
                            menu3.run();
                            break;

                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
	window.draw(rect);
	window.draw(text);

	window.display();
}





