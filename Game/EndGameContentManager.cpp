#include "stdafx.h"
#include "EndGameContentManager.h"

bool EndGameContentManager::loadContent()
{
	if (!endTexture.loadFromFile("Assets\\Sprites\\End.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
	{
		return false;
	}

	return true;
}

const sf::Texture& EndGameContentManager::getEndTexture() const
{
	return endTexture;
}

const sf::Font& EndGameContentManager::getFont() const
{
	return font;
}

EndGameContentManager::EndGameContentManager()
	: ContentManager()
{
}

