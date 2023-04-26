#include "stdafx.h"
#include "TitleContentManager.h"

bool TitleContentManager::loadContent()
{
	if (!titleTexture.loadFromFile("Assets\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
	{
		return false;
	}

	return true;
}

const sf::Texture& TitleContentManager::getTitleTexture() const
{
	return titleTexture;
}

const sf::Font& TitleContentManager::getFont() const
{
	return font;
}

TitleContentManager::TitleContentManager()
	: ContentManager()
{
}

