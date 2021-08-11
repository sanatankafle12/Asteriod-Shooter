#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>


class Boss :
    public Enemy
{
public:
    void init();
    void update(float deltaTime, Vector2f position);
    //CircleShape getSprite();
    sf::Sprite getSprite();
    float getSpawnTime();
    void setTimeCount(float count);
    float getTimeCount();
    void updateTimeCount(float count);

private:
    float movingAngle;
    //CircleShape circle;
    sf::Sprite circle;
    sf::Texture CircleTexture;
    float spawnTime;
    float timeCount;
};

