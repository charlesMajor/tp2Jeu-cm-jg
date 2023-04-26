#pragma once
#include "ContentManager.h"
class TitleContentManager : public ContentManager
{
public:
	TitleContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getTitleTexture() const;
	const sf::Font& getFont() const;

private:
	sf::Texture titleTexture;
	sf::Font font;
};



