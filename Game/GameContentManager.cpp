#include "stdafx.h"
#include "GameContentManager.h"

bool GameContentManager::loadContent()
{

	if (!frontLineEnemyTexture.loadFromFile("Assets\\Sprites\\frontLineEnemy.png"))
	{
		return false;
	}

	if (!attackEnemyTexture.loadFromFile("Assets\\Sprites\\attackEnemy.png"))
	{
		return false;
	}

	if (!backLineEnemyTexture.loadFromFile("Assets\\Sprites\\backLineEnemy.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
	{
		return false;
	}

	return true;
}

const sf::Texture& GameContentManager::getFrontLineEnemyTexture() const
{
	return frontLineEnemyTexture;
}

const sf::Texture& GameContentManager::getAttackEnemyTexture() const
{
	return attackEnemyTexture;
}

const sf::Texture& GameContentManager::getBackLineEnemyTexture() const
{
	return backLineEnemyTexture;
}

const sf::Font& GameContentManager::getFont() const
{
	return font;
}

GameContentManager::GameContentManager()
: ContentManager()
{
}

