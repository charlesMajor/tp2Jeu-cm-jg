#pragma once
#include "GameObject.h"
class Pokeball : public GameObject
{
	static const float MOVE_SPEED;
public:
	Pokeball();
	void stop();
	void update(const float timeElapsed, const sf::Vector2f& destination);

	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
private:
	void setDestination(const sf::Vector2f& destination);
	bool isCloseTo(const sf::Vector2f& position);
	sf::Vector2f destination;
	float moveAngle;
};



