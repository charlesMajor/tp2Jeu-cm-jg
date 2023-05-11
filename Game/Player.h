#pragma once
#include "GameObject.h"
#include "AnimatedGameObject.h"

class Player : public AnimatedGameObject
{
public:
	static const int MAX_LIFE;
	static const float OPACITY_GAIN;
	static const float BASE_SPEED;
	static const int SLOW_TIME;

	Player();
	virtual bool init(const ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	const void onHit();
	const int getLifeLeft();
	void slow(int amountBackEnemies);
	const bool isSlowed();

private:
	void handleOutOfBoundsPosition();
	const void death();

	float currentSpeed;
	int life;
	bool isHit;
	int timeSlowed = 0;
};