#include "stdafx.h"
#include "Pokeball.h"
#include "gamescene.h"

const float Pokeball::MOVE_SPEED = 300.0f;

Pokeball::Pokeball()
  : GameObject()
  , destination(0, 0)
  , moveAngle(0)
{
  activate();
}

void Pokeball::setDestination(const sf::Vector2f& dest)
{
  destination.x = dest.x;
  destination.y = dest.y;

  //On obtient l'angle par le rapport des y sur les x
  moveAngle = atan2f((destination.y - getPosition().y), (destination.x - getPosition().x));
}
bool Pokeball::isCloseTo(const sf::Vector2f& position)
{
  bool isClose = false;
  // pythagore
  float threshold = MOVE_SPEED * GameScene::TIME_PER_FRAME;
  if ((getPosition().x - position.x) * (getPosition().x - position.x) + (getPosition().y - position.y) * (getPosition().y - position.y) < threshold * threshold)
    isClose = true;
  return isClose;
}
void Pokeball::update(const float timeElapsed, const sf::Vector2f& destination)
{
  setDestination(destination);

  if (isCloseTo(destination))
  {
    //On peut la fixer pour être certain
    setPosition(destination);
  }
  else
  {
    float moveDistance = timeElapsed * MOVE_SPEED;
    //On se déplace à partir de l'angle
    move(cos(moveAngle) * moveDistance, sin(moveAngle) * moveDistance);
  }
}

void Pokeball::stop()
{
  setDestination(getPosition());
}

void Pokeball::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
  GameObject::initialize(texture, initialPosition);
  setDestination(initialPosition);
  moveAngle = 0;
}
