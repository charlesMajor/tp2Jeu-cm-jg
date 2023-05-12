#include "stdafx.h"
#include "ContentManager.h"
#include "game.h"
#include "Bonus.h"
#include "Publisher.h"

const float Bonus::BONUS_SPEED = 300;
const float Bonus::BONUS_SCORE = 150;

Bonus::Bonus(const sf::Vector2f& initialPosition)
	: GameObject()
{
	setPosition(initialPosition);
}

void Bonus::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

bool Bonus::update(float elapsedTime)
{
	move(sf::Vector2f(cos(getRotationAngleInRadians()) * BONUS_SPEED * elapsedTime, sin(getRotationAngleInRadians()) * BONUS_SPEED * elapsedTime));
	if (getPosition().y > Game::WORLD_HEIGHT)
	{
		deactivate();
		return true;
	}
	return false;
}

Bonus::Bonus(const Bonus& src)
	: GameObject(src)
{
	GameObject::initialize(*src.getTexture(), src.getPosition());
}

void Bonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	GameObject::initialize(texture, initialPosition);
}

void Bonus::deactivate()
{
	GameObject::deactivate();
	Publisher::notifySubscribers(Event::BONUS_ACQUIRED, nullptr);
}