#include "stdafx.h"
#include "Player.h"
#include "game.h"
#include "PlayerExplodingAnimation.h"
#include "PlayerIdleAnimation.h"
#include "Inputs.h"
#include <iostream>

const int Player::MAX_LIFE = 5;
const float Player::OPACITY_GAIN = 2.0f;
const float Player::BASE_SPEED = 1;
const int Player::SLOW_TIME = 3 * Game::FRAME_RATE;

Player::Player()
  : AnimatedGameObject()
  , life(MAX_LIFE)
  , isHit(false)
{
    currentSpeed = BASE_SPEED;
  activate();
}

bool Player::init(const ContentManager& contentManager)
{
    activate();
    setPosition(sf::Vector2f(Game::GAME_WIDTH / 2, Game::GAME_HEIGHT - 100.0f));

    currentState = State::IDLE;
    bool retval = addAnimation<State::IDLE, PlayerIdleAnimation>(contentManager);
    retval = addAnimation<State::EXPLODING, PlayerExplodingAnimation>(contentManager) && retval;

    return retval && AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
    if (isHit)
    {
        int opacity = getColor().a;

        if (opacity < 255 - OPACITY_GAIN) {
            if (timeSlowed > 0)
            {
                setColor(sf::Color(0, 0, 255, opacity + OPACITY_GAIN));
            }
            else
            {
                setColor(sf::Color(255, 255, 255, opacity + OPACITY_GAIN));
            }
        } else {
            isHit = false;
        }
    }

    if (timeSlowed > 0)
    {
        timeSlowed--;
        if (!isHit)
        {
            this->setColor(sf::Color(0, 0, 255));
        }
    }
    else if (timeSlowed == 0 && !isHit)
    {
        currentSpeed = BASE_SPEED;
        setColor(sf::Color(255, 255, 255));
    }

    move(sf::Vector2f(inputs.moveFactor * currentSpeed, 0));
    handleOutOfBoundsPosition();

    return AnimatedGameObject::update(deltaT, inputs);
}

void Player::handleOutOfBoundsPosition()
{
    sf::Vector2f newPosition = getPosition();
    if (newPosition.x > Game::WORLD_WIDTH - getGlobalBounds().width / 2.0f)
    {
        newPosition.x = Game::WORLD_WIDTH - getGlobalBounds().width / 2.0f;
    }
    else if (newPosition.x < 0.0f + getGlobalBounds().width / 2.0f)
    {
        newPosition.x = 0.0f + getGlobalBounds().width / 2.0f;
    }
    setPosition(newPosition);
}

const int Player::getLifeLeft()
{
    return life;
}

const void Player::onHit()
{
    
    if (!isHit)
    {
        isHit = true;
        life--;
        if (timeSlowed > 0)
        {
            setColor(sf::Color(0, 0, 255, 0));
        }
        else
        {
            setColor(sf::Color(255, 255, 255, 0));
        }
    }

    if (life <= 0)
        death();

    
}

const void Player::death()
{
    currentState = State::EXPLODING;
}

void Player::slow(int amountBackEnemies)
{
    if (amountBackEnemies > 0)
    {
        currentSpeed = BASE_SPEED - (0.1 * amountBackEnemies);
        timeSlowed = SLOW_TIME;
    }
}

const bool Player::isSlowed()
{
    if (timeSlowed > 0)
    {
        return true;
    }
    return false;
}