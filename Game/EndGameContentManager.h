#pragma once
#include "ContentManager.h"

class EndGameContentManager : public ContentManager
{
public:
	EndGameContentManager();
	virtual bool loadContent() override;
	const sf::Font& getFont() const;

private:
	sf::Font font;
};