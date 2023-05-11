#pragma once
#include "Enemy.h"

class BackLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
	static const int AMOUNT_POINTS_FOR_SLOW;
public:
	BackLineEnemy();
	BackLineEnemy(const BackLineEnemy& src);
	bool initialize(const GameContentManager& contentManager, const sf::Vector2f& initialPosition) override;
	bool update(float elapsedTime, int currentPoints, bool playerSlowed);
	void activate() override;
	void onHit() override;
private:
	int health;
};

