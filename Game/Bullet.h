#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
	static const float BULLET_SPEED;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	Bullet& operator=(const Bullet& rhs);
	void draw(sf::RenderWindow& window) const;
	bool update(float elapsedTime);
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb);
	virtual void activate() override;

private:
	sf::Sound bulletSound;
};