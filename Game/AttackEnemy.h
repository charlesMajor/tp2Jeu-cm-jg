#pragma once
#include "Enemy.h"

class AttackEnemy : public Enemy
{
	static const int BASE_HEALTH;
	static const int MAX_RECOIL;
public:
	AttackEnemy();
	AttackEnemy(const AttackEnemy& src);
	void initialize(const sf::Texture & texture, const sf::Vector2f & initialPosition) override;
	bool update(float elapsedTime, sf::Vector2f playerPosition);
	void activate() override;
	void onHit() override;
	int getAngleForBullet();
private:
	int bulletAngle = 90;
	int health;
	int recoil = 0;
};