#pragma once
#include "GameObject.h"
#include "GameContentManager.h"
class Enemy;
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(const Enemy& src);
	void draw(sf::RenderWindow& window) const;
	virtual bool initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) = 0;
	virtual bool update(float elapsedTime) override;
	virtual void onHit() = 0;
	virtual void onDeath() = 0;
private:
	void move();

	sf::Vector2f initialPosition();
};
