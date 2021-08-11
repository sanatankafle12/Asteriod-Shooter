#include "TrackingAsteroid.h"
#include <math.h>
void TrackingAsteroid::init()
{
    enemyTexture.loadFromFile("asteriod.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(0.25,0.25));
    factor = 50;
    rotation = rand() % 361;
    enemy.setRotation(rotation);
    enemy.setPosition(500, 500);
    //angle = enemy.getRotation() / 180 * M_PI - M_PI / 2;
    //velocity = Vector2f(std::cos(angle), std::sin(angle));
    hitCount = 0;
    noOfHitsRequired = 1;
    normalAsteroid = false;
}
void TrackingAsteroid::update(float deltaTime, Vector2f position)
{
    float postionX = position.x - enemy.getPosition().x;
    float postionY = position.y - enemy.getPosition().y;
    float distance = sqrtf(postionX * postionX + postionY * postionY);
    enemy.move((Vector2f(postionX, postionY) / distance) * deltaTime * (float)factor);
}