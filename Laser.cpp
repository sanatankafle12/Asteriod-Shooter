#include "Laser.h"
#include <math.h>

using namespace sf;

Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::update(float deltaTime)
{
	float angle = rotation / 180 * M_PI - M_PI / 2;
	laser.move(Vector2f(cos(angle), sin(angle)) * deltaTime * factor);
}

void Laser::init(Vector2f position, float Rotation)
{

	rotation = Rotation;
	laserTexture.loadFromFile("laser.png");
	laser.setTexture(laserTexture);
	laser.setPosition(position.x,position.y);
	laser.setRotation(rotation);
	factor = 800;
}

Sprite Laser::getSprite()
{
	return laser;
}
