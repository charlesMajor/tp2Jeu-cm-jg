#pragma once
#include "Enemy.h"

class BackLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
public:
	BackLineEnemy();
	BackLineEnemy(const BackLineEnemy& src);
	bool initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) override;
	bool update(float elapsedTime) override;
};

