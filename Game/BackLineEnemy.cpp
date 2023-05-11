#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"
#include <iostream>

const int BackLineEnemy::BASE_HEALTH = 3;
const int BackLineEnemy::AMOUNT_POINTS_FOR_SLOW = 1000;

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

bool BackLineEnemy::update(float elapsedTime, int currentPoints, bool playerSlowed)
{
    Enemy::update(elapsedTime);
    if (currentPoints % AMOUNT_POINTS_FOR_SLOW == 0 && currentPoints != 0 && !playerSlowed)
    {
        return true;
    }

    if (playerSlowed)
    {
        this->setColor(sf::Color::Blue);
    }
    else
    {
        this->setColor(sf::Color(255, 255, 255));
    }
    return false;
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