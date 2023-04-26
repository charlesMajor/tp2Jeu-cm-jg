#pragma once
#include "ContentManager.h"
class EndGameContentManager : public ContentManager
{
public:
	EndGameContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getEndTexture() const;
	const sf::Font& getFont() const;

private:
	sf::Texture endTexture;
	sf::Font font;
};



