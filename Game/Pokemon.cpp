#include "stdafx.h"
#include "Pokemon.h"
#include "Pokeball.h"
#include "game.h"

const float Pokemon::DEFAULT_JUMP_SPEED = 3.0f;

Pokemon::Pokemon()
  : GameObject()
  , jumpSpeed(Pokemon::DEFAULT_JUMP_SPEED)
  , timeBeforeJump(Pokemon::DEFAULT_JUMP_SPEED)
{
  activate();
}

void Pokemon::loadPokemonSpeaks(const sf::SoundBuffer& soundbuffer)
{
  pokemonSpeaks.setBuffer(soundbuffer);
}

void Pokemon::setJumpSpeed(float jumpSpeed)
{
  this->jumpSpeed = timeBeforeJump = jumpSpeed;
}


void Pokemon::jump()
{
  timeBeforeJump = jumpSpeed;

  setPosition((rand() % (int)(Game::GAME_WIDTH - getGlobalBounds().width)) + getGlobalBounds().width / 2,
    (rand() % (int)(Game::GAME_HEIGHT - getGlobalBounds().height)) + getGlobalBounds().height / 2);

}

void Pokemon::speak()
{
  pokemonSpeaks.play();
}


void Pokemon::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
  GameObject::initialize(texture, initialPosition);
  setJumpSpeed(DEFAULT_JUMP_SPEED);
  jump();
}

bool Pokemon::update(float elapsedTime)
{
  bool retval = false;
  timeBeforeJump = std::max(timeBeforeJump - elapsedTime, 0.0f);
  if (timeBeforeJump == 0.0f)
  {
    jump();
    retval = true;
  }

  return retval;
}

void Pokemon::onCatched()
{
  jump();
  speak();
}