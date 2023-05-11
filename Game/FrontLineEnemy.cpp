#include "stdafx.h"
#include "FrontLineEnemy.h"
#include "game.h"
#include <iostream>

const int FrontLineEnemy::BASE_HEALTH = 4;
const int FrontLineEnemy::SHIELD_TIME = 2 * Game::FRAME_RATE;

FrontLineEnemy::FrontLineEnemy()
    : Enemy()
{
    this->activate();
}

FrontLineEnemy::FrontLineEnemy(const FrontLineEnemy& src)
    : Enemy(src)
{
    health = src.health;
    timeLeftShield = src.timeLeftShield;
}

bool FrontLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getFrontLineEnemyTexture(), initialPosition);
    return true;
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
    {
        health--;
        if (health <= 0)
        {
            this->onDeath();
        }
    }
    
    if (health == 1)
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
        this->onDeath();
    }
}