#include "stdafx.h"
#include "Enemy.h"
#include "game.h"

Enemy::Enemy()
  : AnimatedGameObject()
{
}

Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src)
{
    setTexture(*src.getTexture());

    setPosition(src.getPosition());
    if (src.isActive())
        activate();
    else
        deactivate();
}

void Enemy::draw(sf::RenderWindow& window) const
{
    window.draw(*this);
}

void Enemy::move()
{
  setPosition((rand() % (int)(Game::GAME_WIDTH - getGlobalBounds().width)) + getGlobalBounds().width / 2,
    (rand() % (int)(Game::GAME_HEIGHT - getGlobalBounds().height)) + getGlobalBounds().height / 2);
}

bool Enemy::update(float elapsedTime)
{
    return true;
}