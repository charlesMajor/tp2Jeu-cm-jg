#pragma once
#include "GameObject.h"
#include "AnimatedGameObject.h"

class Player : public AnimatedGameObject
{
public:
	static const int MAX_LIFE;
	static const int OPACITY_GAIN;

	Player();
	virtual bool init(const ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	const void onHit();
	const int getLifeLeft();

private:
	void handleOutOfBoundsPosition();
	const void death();

	int life;
	bool isHit;
};