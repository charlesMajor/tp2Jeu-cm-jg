#include "stdafx.h"
#include "Player.h"
#include "game.h"
#include "PlayerExplodingAnimation.h"
#include "PlayerIdleAnimation.h"
#include "Inputs.h"

const int Player::MAX_LIFE = 5;
const int Player::OPACITY_GAIN = 2;

Player::Player()
  : AnimatedGameObject()
  , life(MAX_LIFE)
  , isHit(false)
{
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
            setColor(sf::Color(255, 255, 255, opacity + OPACITY_GAIN));
        } else {
            isHit = false;
        }
    }

    move(sf::Vector2f(inputs.moveFactor, 0));
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
    life--;

    if (life <= 0) {
        death();
    } else {
        isHit = true;
        setColor(sf::Color(255, 255, 255, 0));
    }
}

const void Player::death()
{
    currentState = State::EXPLODING;
}