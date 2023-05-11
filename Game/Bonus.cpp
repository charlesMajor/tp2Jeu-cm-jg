#include "stdafx.h"
#include "ContentManager.h"
#include "game.h"
#include "Bonus.h"

const float Bonus::BONUS_SPEED = 600;

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
	setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Bonus::deactivate()
{
	this->soundBonus.play();
	GameObject::deactivate();
}

void Bonus::setBonusBuffer(const sf::SoundBuffer& sb)
{
	soundBonus.setBuffer(sb);
}