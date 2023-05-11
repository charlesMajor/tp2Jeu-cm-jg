#pragma once
#include "GameObject.h"
#include "GameContentManager.h"
class Enemy;
class Enemy : public GameObject
{
	static const float MOVE_SPEED;
public:
	Enemy();
	Enemy(const Enemy& src);
	void draw(sf::RenderWindow& window) const;
	virtual bool initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) = 0;
	bool isCloseTo(const sf::Vector2f& position);
	virtual bool update(float elapsedTime) override;
	virtual void activate(bool leftFirst, int distance);
	virtual void onHit() = 0;
	virtual void onDeath();
private:
	bool leftFirst;
	int distance;
	std::list<sf::Vector2f> sideLimits;
	sf::Vector2f currentDirection;
	sf::Vector2f initialPosition();
};
