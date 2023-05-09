#pragma once
#include "AnimatedGameObject.h"
#include "GameContentManager.h"
class Enemy;
class Enemy : public AnimatedGameObject
{
public:
	Enemy();
	Enemy(const Enemy& src);
	void draw(sf::RenderWindow& window) const;
	virtual void initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) = 0;
	virtual bool update(float elapsedTime) override;
private:
	void move();

	sf::Vector2f initialPosition();
};
