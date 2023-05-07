#include "stdafx.h"
#include "BackLineEnemy.h"
#include "game.h"

static const int BASE_HEALTH = 10;

BackLineEnemy::BackLineEnemy()
    : Enemy()
{
}
BackLineEnemy::BackLineEnemy(const BackLineEnemy& src)
    : Enemy(src)
{
}

void BackLineEnemy::initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(contentManager.getBackLineEnemyTexture(), initialPosition);
}

bool BackLineEnemy::update(float elapsedTime)
{
    return true;
}