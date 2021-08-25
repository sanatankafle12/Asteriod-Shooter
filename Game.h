#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include "Player.h"
#include "Laser.h"
#include"Enemy.h"
#include"BigAsteroid.h"
#include"SmallAsteroid.h"
#include"MediumAsteroid.h"
#include"TrackingAsteroid.h"
#include "Boss.h"
#include "slingingAsteroid.h"
using namespace sf;
class Game
{
public:
	Game();
	~Game();
	void run();
	void init();


private:
	static int level;
	static int finalLevel;
	static int score;
	void processEvent();
	void update(float deltaTime);
	void spawnEnemies();
	void clearMemory();
	Enemy* chooseEnemy(int i);
	void render();
	void shoot();
	RenderWindow window;
	Texture backgoundTexture;
	Sprite backgroundSprite;
	Player player;
	bool gameOver;
	void gameWonScreen();
	void gameOverScreen();
	std::vector<Laser*>lasers;
	std::vector<Enemy*>enemies;
	std::vector<Boss*>bosses;
	bool gameWon;

};

