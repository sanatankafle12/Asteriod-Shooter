#include<SFML/Graphics.hpp>

#include <math.h>
#pragma once
using namespace sf;
class Laser
{
public:
	Laser();
	~Laser();
	void update(float deltaTime);
	void init(Vector2f position,float rotation);
	Sprite getSprite();
private:
	Texture laserTexture;
	Sprite laser;

	float factor ;
	float rotation;
};

