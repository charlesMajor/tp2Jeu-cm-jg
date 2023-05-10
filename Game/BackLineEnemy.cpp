#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"

const int BackLineEnemy::BASE_HEALTH = 10;

BackLineEnemy::BackLineEnemy()
    : Enemy()
{
}

BackLineEnemy::BackLineEnemy(const BackLineEnemy& src)
    : Enemy(src)
{
}

bool BackLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getBackLineEnemyTexture(), initialPosition);
    health = BASE_HEALTH;
    return true;
}

bool BackLineEnemy::update(float elapsedTime)
{
    return true;
}

void BackLineEnemy::onHit()
{
    health--;
    if (health <= 0)
    {
        this->onDeath();
    }
}

void BackLineEnemy::onDeath()
{
    this->deactivate();
}