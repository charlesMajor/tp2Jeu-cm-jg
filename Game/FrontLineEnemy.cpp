#include "stdafx.h"
#include "FrontLineEnemy.h"
#include "game.h"
#include <iostream>

const int FrontLineEnemy::BASE_HEALTH = 2;
const int FrontLineEnemy::SHIELD_TIME = 5 * Game::FRAME_RATE;
const int FrontLineEnemy::DESTRUCTION_SCORE = 50;
const int FrontLineEnemy::HEALTH_SHIELD_TRIGGER = 1;

FrontLineEnemy::FrontLineEnemy()
    : Enemy()
    , health(BASE_HEALTH)
    , isShielded(false)
{
    this->activate();
}

FrontLineEnemy::FrontLineEnemy(const FrontLineEnemy& src)
    : Enemy(src)
{
    health = src.health;
    timeLeftShield = src.timeLeftShield;
    isShielded = src.isShielded;
}

void FrontLineEnemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(texture, initialPosition);
}

bool FrontLineEnemy::update(float elapsedTime) 
{
    Enemy::update(elapsedTime);
    if (this->isShielded)
    {
        this->shield();
    }
    return true;
}

void FrontLineEnemy::activate()
{
    health = BASE_HEALTH;
    timeLeftShield = SHIELD_TIME;
    Enemy::activate(true, 20);
}

void FrontLineEnemy::onHit()
{
    if (!this->isShielded)
        health--;
    
    if (health == HEALTH_SHIELD_TRIGGER)
    {
        this->isShielded = true;
        health = 0;
    }
}

void FrontLineEnemy::shield()
{
    timeLeftShield--;
    this->setColor(sf::Color::Cyan);
    if (timeLeftShield <= 0)
    {
        this->onDeath(DESTRUCTION_SCORE, *this);
    }
}