#pragma once
#include "ContentManager.h"
class GameContentManager : public ContentManager
{
public:
	GameContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBulbasaurTexture() const;
	const sf::SoundBuffer& getBulbasaurSoundBuffer() const;
	const sf::Texture& getPokeballTexture() const;
	const sf::Font& getFont() const;

private:
	sf::Texture bulbasaurTexture;
	sf::Texture pokeballTexture;
	sf::SoundBuffer bulbasaurSoundBuffer;
	sf::Font font;
};



