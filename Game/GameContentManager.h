#pragma once
#include "ContentManager.h"

class GameContentManager : public ContentManager
{
public:
	GameContentManager();
	virtual bool loadContent() override;
	
	const sf::Texture& getPlayerAnimationTexture() const;
	const sf::SoundBuffer& getPlayerShotSoundBuffer() const;
	const sf::SoundBuffer& getEnemyShotSoundBuffer() const;

	const sf::Texture& getFrontLineEnemyTexture() const;
	const sf::Texture& getAttackEnemyTexture() const;
	const sf::Texture& getBackLineEnemyTexture() const;
	
	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getBulletTexture() const;
	const sf::Texture& getBonusTexture() const;
	const sf::SoundBuffer& getBonusSoundBuffer() const;
	const sf::Font& getFont() const;

private:
	sf::Texture playerAnimationTexture;
	sf::SoundBuffer playerShotSoundBuffer;
	
	sf::Texture frontLineEnemyTexture;
	sf::Texture attackEnemyTexture;
	sf::Texture backLineEnemyTexture;
	sf::SoundBuffer enemyShotSoundBuffer;
	
	sf::Texture backgroundTexture;
	sf::Texture bulletTexture;
	sf::Texture bonusTexture;
	sf::SoundBuffer bonusSoundBuffer;
	sf::Font font;
};