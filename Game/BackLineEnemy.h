#pragma once
#include "Enemy.h"

class BackLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
public:
	BackLineEnemy();
	BackLineEnemy(const BackLineEnemy& src);
	void initialize(const sf::Texture & texture, const sf::Vector2f & initialPosition) override;
	bool update(float elapsedTime) override;
	void activate() override;
	void onHit() override;
private:
	int health;
};