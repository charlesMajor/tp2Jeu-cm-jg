#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"
#include <iostream>

const int BackLineEnemy::BASE_HEALTH = 2;
const int BackLineEnemy::AMOUNT_POINTS_FOR_SLOW = 1000;
const int BackLineEnemy::DESTRUCTION_SCORE = 200;

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
        this->onDeath(DESTRUCTION_SCORE, *this);
    }
}