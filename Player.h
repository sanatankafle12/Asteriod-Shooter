#include<SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#pragma once
using namespace sf;
class Player
{
private:
	bool ismoving;
	int rotation;
	Vector2f position;
	Vector2f velocity;
	void playerMovement(float deltaTime);
	void checkPosition();
	Texture playertexture;
	Sprite player;
	float factor;
public:
	Player();
	~Player();
	void init();
	void updatePlayer(float deltaTime);
	Sprite getSprite();
	void setMoving(bool moving);
	void setRotation(int rot);
	
};

