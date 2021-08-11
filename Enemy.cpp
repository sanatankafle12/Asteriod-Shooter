#include "Enemy.h"
#include <math.h>

Enemy::Enemy()
{
	position.x = 500;
	position.y = 500;
}

Enemy::~Enemy()
{
}

bool Enemy::getAseroidType()
{
	return normalAsteroid;
}

void Enemy::setAsteroidTpye(bool type)
{
	normalAsteroid = type;
}


void Enemy::update(float deltaTime,Vector2f position)
{
	enemy.move(velocity * deltaTime * (float)factor);
	if (enemy.getPosition().x < 0  || enemy.getPosition().x > 1000 ||
		enemy.getPosition().y < 0 || enemy.getPosition().y>720)
	{
		rotation = rotation + 90;
		enemy.setRotation(rotation);
		angle = enemy.getRotation() / 180 * M_PI - M_PI / 2;
		velocity = Vector2f(std::cos(angle), std::sin(angle));
	}
}

Sprite Enemy::getSprite()
{
	return enemy;
}

int Enemy::gethitCount()
{
	return hitCount;
}

int Enemy::getnoOfHitsRequired()
{
	return noOfHitsRequired;
}

void Enemy::setHitcount(int hit)
{
	hitCount = hit;
}

Vector2f Enemy::getPosition()
{
	return enemy.getPosition();
}

void Enemy::setPosition(Vector2f position)
{
	this->position = position;
}

void Enemy::setplayerPosition(Vector2f pos)
{
	playerPosition = pos;
}

