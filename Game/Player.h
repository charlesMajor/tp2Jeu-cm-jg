#pragma once
#include "GameObject.h"
#include "AnimatedGameObject.h"

class Player : public AnimatedGameObject
{
public:
	static const int MAX_LIFE;

	Player();
	virtual bool init(const ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;

	const int getLifeLeft();

private:
	void handleOutOfBoundsPosition();
	const void death();
	const void onHit();

	int life;
	bool isDead; //TODO:: Voir si nécessaire ?
};