#pragma once
#include "GameObject.h"

class Bonus : public GameObject
{
	static const float BONUS_SPEED;
public:
	static const float BONUS_SCORE;

	Bonus(const Bonus& src);
	Bonus(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
	void draw(sf::RenderWindow& window) const;
	bool update(float elapsedTime);
	void collidesWithPlayer();
};