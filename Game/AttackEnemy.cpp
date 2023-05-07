/* Augment la cadence de tir des alliés pour quelques secondes à la mort */
#include "stdafx.h"
#include "AttackEnemy.h"
#include "game.h"

static const int BASE_HEALTH = 10;

AttackEnemy::AttackEnemy()
    : Enemy()
{
}
AttackEnemy::AttackEnemy(const AttackEnemy& src)
    : Enemy(src)
{
}

void AttackEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getAttackEnemyTexture(), initialPosition);
}

bool AttackEnemy::update(float elapsedTime)
{
    return true;
}