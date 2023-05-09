#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 600;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
	: GameObject()
{
	setPosition(initialPosition);
	move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
	:GameObject(src)
{
	GameObject::initialize(*src.getTexture(), src.getPosition());
	this->bulletSound.setBuffer(*src.bulletSound.getBuffer());
}

Bullet& Bullet::operator=(const Bullet& rhs)
{
	if (this != &rhs)
	{
		GameObject::operator=(rhs);
		GameObject::initialize(*rhs.getTexture(), rhs.getPosition());
		this->bulletSound.setBuffer(*rhs.bulletSound.getBuffer());
	}
	return *this;
}

void Bullet::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

bool Bullet::update(float elapsedTime)
{
	move(sf::Vector2f(cos(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime, sin(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime));
	if (getPosition().x > Game::WORLD_WIDTH || getPosition().x < 0 || getPosition().y > Game::WORLD_HEIGHT || getPosition().y < 0)
	{
		deactivate();
		return true;
	}
	return false;
}

void Bullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	GameObject::initialize(texture, initialPosition);

	bulletSound.setBuffer(sb);
}

void Bullet::activate()
{
	bulletSound.play();
	GameObject::activate();
}