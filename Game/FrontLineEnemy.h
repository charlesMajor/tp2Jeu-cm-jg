#pragma once
#include "Enemy.h"

class FrontLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
public:
	FrontLineEnemy();
	FrontLineEnemy(const FrontLineEnemy& src);
	bool initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) override;
	bool update(float elapsedTime) override;
	void onHit() override;
	void onDeath() override;
private:
	int health;
};

