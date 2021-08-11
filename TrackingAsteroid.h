#pragma once
#include "Enemy.h"
class TrackingAsteroid :
    public Enemy
{
    void init();
    void update(float deltaTime, Vector2f position);
};

