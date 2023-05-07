#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	static const float BULLET_SPEED;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	Bullet& operator=(const Bullet& src);
	void draw(sf::RenderWindow& window) const;
	bool update(float elapsedTime, sf::Vector2f topLeftView, sf::Vector2f botRightView);
	void initialize(const ContentManager& contentManager, const sf::Vector2f& initialPosition);
	virtual void activate();
private:
	sf::Sound shotSound;
};