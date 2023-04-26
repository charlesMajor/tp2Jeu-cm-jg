#pragma once
#include "GameObject.h"
class Pokeball;
class Pokemon : public GameObject
{
	static const float DEFAULT_JUMP_SPEED;
public:
	Pokemon();

	void setJumpSpeed(float jumpSpeed);
	void loadPokemonSpeaks(const sf::SoundBuffer& soundbuffer);

	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;

	void onCatched();
	virtual bool update(float elapsedTime) override;
private:
	void speak();
	void jump();

	float jumpSpeed;
	float timeBeforeJump;
	sf::Sound pokemonSpeaks;
};
