#include "stdafx.h"
#include "TitleContentManager.h"

bool TitleContentManager::loadContent()
{
	if (!background.loadFromFile("Assets\\Sprites\\SpaceBackground.png"))
	{
		return false;
	}

	if (!logo.loadFromFile("Assets\\Sprites\\logo.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
	{
		return false;
	}

	return true;
}

const sf::Texture& TitleContentManager::getBackground() const
{
	return background;
}

const sf::Texture& TitleContentManager::getLogo() const
{
	return logo;
}

const sf::Font& TitleContentManager::getFont() const
{
	return font;
}

TitleContentManager::TitleContentManager()
	: ContentManager()
{
}

