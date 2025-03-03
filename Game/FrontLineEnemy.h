#pragma once
#include "Enemy.h"

class FrontLineEnemy : public Enemy
{
	static const int BASE_HEALTH;
	static const int SHIELD_TIME;
	static const int DESTRUCTION_SCORE;
	static const int HEALTH_SHIELD_TRIGGER;
public:
	FrontLineEnemy();
	FrontLineEnemy(const FrontLineEnemy& src);
	void initialize(const sf::Texture & texture, const sf::Vector2f& initialPosition) override;
	void activate() override;
	bool update(float elapsedTime) override;
	void onHit() override;
	void shield();
private:
	int health;
	bool isShielded;
	int timeLeftShield;
};