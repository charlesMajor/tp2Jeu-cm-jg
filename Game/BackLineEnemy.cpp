#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"

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

bool BackLineEnemy::update(float elapsedTime)
{
    Enemy::update(elapsedTime);
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