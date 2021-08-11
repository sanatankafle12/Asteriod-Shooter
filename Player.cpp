#include "Player.h"
#include <math.h>

void Player::playerMovement(float deltaTime)
{
	if (rotation != 0)
	{
		float angle = rotation * factor * deltaTime;
		player.rotate(angle);
	}
	if (ismoving)
	{
		float angle = player.getRotation() / 180 * M_PI -M_PI/2;
		velocity = Vector2f(std::cos(angle), std::sin(angle)) * deltaTime * factor;
		player.move(velocity);
	}

}

void Player::checkPosition()
{
	if (player.getPosition().x < 0)
	{
		player.setPosition(1000, player.getPosition().y);
	}
	else if (player.getPosition().x > 1000)
	{
		player.setPosition(0, player.getPosition().y);
	}
	if (player.getPosition().y < 0)
	{
		player.setPosition(player.getPosition().x, 720);
	}
	else if (player.getPosition().y > 720)
	{
		player.setPosition(player.getPosition().x, 0);
	}
}

void Player::init()
{
	position.x = 500.f;
	position.y = 360.f;
	playertexture.loadFromFile("space.png");
	player.setTexture(playertexture);
	player.setPosition(position);

	factor = 70;

}
Player::Player()
{

	
}

void Player::updatePlayer(float deltaTime)
{
	
	playerMovement(deltaTime);
	checkPosition();
	
}

Player::~Player()
{
}

Sprite Player::getSprite()
{
	return player;
}


void Player::setMoving(bool moving)
{
	ismoving = moving;
}

void Player::setRotation(int rot)
{
	rotation = rot;
}
