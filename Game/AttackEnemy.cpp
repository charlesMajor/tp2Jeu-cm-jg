/* Augment la cadence de tir des alliés pour quelques secondes à la mort */
#include "stdafx.h"
#include "AttackEnemy.h"
#include "game.h"

const int AttackEnemy::BASE_HEALTH = 10;

AttackEnemy::AttackEnemy()
    : Enemy()
{
}

AttackEnemy::AttackEnemy(const AttackEnemy& src)
    : Enemy(src)
{
}

bool AttackEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getAttackEnemyTexture(), initialPosition);
    health = BASE_HEALTH;
    return true;
}

bool AttackEnemy::update(float elapsedTime)
{
    return true;
}

void AttackEnemy::onHit()
{
    health--;
    if (health <= 0)
    {
        this->onDeath();
    }
}

void AttackEnemy::onDeath()
{
    this->deactivate();
}