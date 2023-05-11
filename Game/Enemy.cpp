#include "stdafx.h"
#include "Enemy.h"
#include "game.h"
#include <iostream>

const float Enemy::MOVE_SPEED = 75.0f;

Enemy::Enemy()
  : GameObject()
{
}

Enemy::Enemy(const Enemy& src)
    : GameObject(src)
{
    setTexture(*src.getTexture());

    setPosition(src.getPosition());
    if (src.isActive())
        this->activate(src.leftFirst, src.distance);
    else
        this->deactivate();
}

void Enemy::draw(sf::RenderWindow& window) const
{
    window.draw(*this);
}

bool Enemy::isCloseTo(const sf::Vector2f& position)
{
    bool isClose = false;
    float threshold = 0.1;
    if ((getPosition().x - position.x) * (getPosition().x - position.x) + (getPosition().y - position.y) * (getPosition().y - position.y) < threshold * threshold)
        isClose = true;
    return isClose;
}

bool Enemy::update(float elapsedTime)
{
    if (!isCloseTo(currentDirection))
    {
        float moveDistance = elapsedTime * MOVE_SPEED;
        float moveAngle = atan2f((currentDirection.y - getPosition().y), (currentDirection.x - getPosition().x));
        move(cos(moveAngle) * moveDistance, sin(moveAngle) * moveDistance);
    }
    else
    {
        setPosition(currentDirection);
        for (sf::Vector2f limit : sideLimits)
        {
            if (limit != getPosition())
            {
                currentDirection = limit;
            }
        }
    }
    return true;
}

void Enemy::activate(bool leftFirst, int distance)
{
    sf::Vector2f left = sf::Vector2f(this->getPosition().x - distance, this->getPosition().y);
    sf::Vector2f right = sf::Vector2f(this->getPosition().x + distance, this->getPosition().y);
    this->leftFirst = leftFirst;
    this->distance = distance;
    if (leftFirst)
    {
        sideLimits.push_back(left);
        sideLimits.push_back(right);
    }
    else
    {
        sideLimits.push_back(right);
        sideLimits.push_back(left);
    }
    currentDirection = sideLimits.front();
    this->active = true;
}

void Enemy::onDeath()
{
    this->deactivate();
}