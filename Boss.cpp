#include "Boss.h"
#include <iostream>
#include <math.h>

void Boss::init()
{
	//circle.setFillColor(Color::Green);
	//circle.setRadius(50);
	//circle.setPointCount(3);

	CircleTexture.loadFromFile("boss.png");
	circle.setTexture(CircleTexture);
	circle.setScale(sf::Vector2f(0.25,0.25));
	//circle.setOrigin(circle.getRadius() / (float)2, circle.getRadius() / (float)2);
	factor = 70;
	rotation = rand() % 361;
	circle.setPosition(700,500);
	angle = circle.getRotation() / 180 * M_PI - M_PI / 2;
	velocity = Vector2f(std::cos(angle), std::sin(angle));
	hitCount = 0;
	noOfHitsRequired = 20;
	normalAsteroid = true;
	spawnTime = 8.0f;
	timeCount = 0;
}

void Boss::update(float deltaTime, Vector2f position)
{
	circle.move(velocity * deltaTime * (float)factor);
	if (circle.getPosition().x < 0 || circle.getPosition().x > 1000 ||
		circle.getPosition().y < 0 || circle.getPosition().y>720)
	{
		rotation = rotation + 90;
		circle.rotate(rotation);
		angle = circle.getRotation() / 180 * M_PI - M_PI / 2;
		velocity = Vector2f(std::cos(angle), std::sin(angle));
	}
}

Sprite Boss::getSprite()
{
	return circle;
}

float Boss::getSpawnTime()
{
	return spawnTime;
}

void Boss::setTimeCount(float count)
{
	timeCount =count;
}

float Boss::getTimeCount()
{
	return timeCount;
}

void Boss::updateTimeCount(float count)
{
	timeCount += count;
}
