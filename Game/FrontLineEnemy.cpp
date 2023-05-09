/* Devient invincible pour quelques secondes lorsqu'il n'a presque plus de vie */
#include "stdafx.h"
#include "FrontLineEnemy.h"
#include "game.h"

static const int BASE_HEALTH = 10;

FrontLineEnemy::FrontLineEnemy()
    : Enemy()
{
}

FrontLineEnemy::FrontLineEnemy(const FrontLineEnemy& src)
    : Enemy(src)
{
}

void FrontLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getFrontLineEnemyTexture(), initialPosition);
}

bool FrontLineEnemy::update(float elapsedTime)
{
    return true;
}