#pragma once
#include "Enemy.h"

class BackLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
	static const int AMOUNT_POINTS_FOR_SLOW;
	static const int DESTRUCTION_SCORE;
public:
	BackLineEnemy();
	BackLineEnemy(const BackLineEnemy& src);
	void initialize(const sf::Texture & texture, const sf::Vector2f & initialPosition) override;
	bool update(float elapsedTime, int currentPoints, bool playerSlowed);
	void activate() override;
	void onHit() override;
private:
	int health;
};