#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"
#include <iostream>

const int BackLineEnemy::BASE_HEALTH = 3;

BackLineEnemy::BackLineEnemy()
    : Enemy()
{
    this->activate();
}

BackLineEnemy::BackLineEnemy(const BackLineEnemy& src)
    : Enemy(src)
{
    health = src.health;
}

bool BackLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getBackLineEnemyTexture(), initialPosition);
    health = BASE_HEALTH;
    return true;
}

bool BackLineEnemy::update(float elapsedTime, int currentPoints)
{
    Enemy::update(elapsedTime);
    if (currentPoints % 100 == 0)
    {
        return true;
    }
    return true;
}

void BackLineEnemy::activate()
{
    health = BASE_HEALTH;
    Enemy::activate(false, 20);
}

void BackLineEnemy::onHit()
{
    health--;
    if (health <= 0)
    {
        this->onDeath();
    }
}