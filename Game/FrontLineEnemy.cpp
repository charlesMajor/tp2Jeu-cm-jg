/* Devient invincible pour quelques secondes lorsqu'il n'a presque plus de vie */
#include "stdafx.h"
#include "FrontLineEnemy.h"
#include "game.h"

const int FrontLineEnemy::BASE_HEALTH = 4;

FrontLineEnemy::FrontLineEnemy()
    : Enemy()
{
}

FrontLineEnemy::FrontLineEnemy(const FrontLineEnemy& src)
    : Enemy(src)
{
}

bool FrontLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getFrontLineEnemyTexture(), initialPosition);
    //health = BASE_HEALTH;
    return true;
}

bool FrontLineEnemy::update(float elapsedTime)
{
    if (health == 2)
    {

    }
    return true;
}

void FrontLineEnemy::onHit()
{
    health--;
    if (health <= 0)
    {
        this->onDeath();
    }
}

void FrontLineEnemy::onDeath()
{
    this->deactivate();
}