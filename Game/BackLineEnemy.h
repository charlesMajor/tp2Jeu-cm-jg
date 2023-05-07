#pragma once
#include "Enemy.h"
class BackLineEnemy;
class BackLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
public:
	BackLineEnemy();
	BackLineEnemy(const BackLineEnemy& src);
	void initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) override;
	bool update(float elapsedTime) override;
private:
};

