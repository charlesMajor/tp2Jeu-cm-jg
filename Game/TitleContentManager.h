#pragma once
#include "ContentManager.h"

class TitleContentManager : public ContentManager
{
public:
	TitleContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackground() const;
	const sf::Texture& getLogo() const;
	const sf::Font& getFont() const;

private:
	sf::Texture background;
	sf::Texture logo;
	sf::Font font;
};