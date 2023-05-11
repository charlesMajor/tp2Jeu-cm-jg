#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"

const int BackLineEnemy::BASE_HEALTH = 1;

BackLineEnemy::BackLineEnemy()
    : Enemy()
    , health(BASE_HEALTH)
{
    this->activate();
}

BackLineEnemy::BackLineEnemy(const BackLineEnemy& src)
    : Enemy(src)
{
    health = src.health;
}

void BackLineEnemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(texture, initialPosition);
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