#include "SmallAsteroid.h"
#include <math.h>

void SmallAsteroid::init()
{
    //enemy.setFillColor(Color::Green);
    //enemy.setSize(Vector2f(25, 25));
    //enemy.setOrigin(enemy.getSize() / (float)2);
    enemyTexture.loadFromFile("asteriod.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(0.2,0.2));
    factor = 70;
    rotation = rand() % 361;
    enemy.setRotation(rotation);
    enemy.setPosition(position);
    angle = enemy.getRotation() / 180 * M_PI - M_PI / 2;
    velocity = Vector2f(std::cos(angle), std::sin(angle));
    hitCount = 0;
    noOfHitsRequired = 1;
    normalAsteroid = true;
}
