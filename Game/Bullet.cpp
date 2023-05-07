#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "game.h"
#include <iostream>

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
	this->setTexture(*src.getTexture());
	this->setPosition(src.getPosition());
	this->shotSound.setBuffer(*src.shotSound.getBuffer());
}
Bullet& Bullet::operator=(const Bullet& rhs)
{
	if (this != &rhs)
	{
		GameObject::operator=(rhs);
		this->setTexture(*rhs.getTexture());
		this->setPosition(rhs.getPosition());
		this->shotSound.setBuffer(*rhs.shotSound.getBuffer());
	}
	return *this;
}

void Bullet::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}


bool Bullet::update(float elapsedTime, sf::Vector2f topLeftView, sf::Vector2f botRightView)
{
	move(sf::Vector2f(cos(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime, sin(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime));
	if (getPosition().x > botRightView.x || getPosition().x < topLeftView.x || getPosition().y > botRightView.y || getPosition().y < topLeftView.y)
		this->deactivate();
	return true;
	return false;
}

/*void Bullet::initialize(const ContentManager& contentManager, const sf::Vector2f& initialPosition)
{
	GameObject::initialize(contentManager.getNormalBulletTexture(), initialPosition);

	shotSound.setBuffer(contentManager.getShotSoundBuffer());
}*/

void Bullet::activate()
{
	active = true;
	this->shotSound.play();
}