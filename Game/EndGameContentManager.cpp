#include "stdafx.h"
#include "EndGameContentManager.h"

bool EndGameContentManager::loadContent()
{
	if (!font.loadFromFile("Assets\\Fonts\\ChunkFive-Regular.otf"))
		return false;

	return true;
}

const sf::Font& EndGameContentManager::getFont() const
{
	return font;
}

EndGameContentManager::EndGameContentManager()
	: ContentManager()
{
}