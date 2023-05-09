#pragma once
#include "Enemy.h"

class AttackEnemy : public Enemy
{
	static const int BASE_HEALTH;
public:
	AttackEnemy();
	AttackEnemy(const AttackEnemy& src);
	void initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) override;
	bool update(float elapsedTime) override;
};

