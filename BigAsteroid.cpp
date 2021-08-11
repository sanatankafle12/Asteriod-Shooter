#include "BigAsteroid.h"
#include <math.h>

using namespace sf;

void BigAsteroid::init()
{
    //enemy.setFillColor(Color::Green);
    //enemy.setSize(Vector2f(50, 50));
    //enemy.setOrigin(enemy.getSize() / (float)2);
    enemyTexture.loadFromFile("asteriod.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(sf::Vector2f(0.5,0.5));
    factor = 40;
    rotation = rand() % 361;
    enemy.setRotation(rotation);
    enemy.setPosition(position);
    angle = enemy.getRotation() / 180 * M_PI - M_PI / 2;
    velocity = Vector2f(std::cos(angle), std::sin(angle));
    hitCount = 0;
    noOfHitsRequired = 3;
    normalAsteroid = true;
}
