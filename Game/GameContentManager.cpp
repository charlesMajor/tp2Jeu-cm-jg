#include "stdafx.h"
#include "GameContentManager.h"

bool GameContentManager::loadContent()
{
	if (!playerAnimationTexture.loadFromFile("Assets\\Sprites\\PlayerShip.png"))
		return false;

	if (!playerShotSoundBuffer.loadFromFile("Assets\\Sounds\\Shot01.ogg"))
		return false;
	
	if (!frontLineEnemyTexture.loadFromFile("Assets\\Sprites\\frontLineEnemy.png"))
		return false;
	
	if (!attackEnemyTexture.loadFromFile("Assets\\Sprites\\attackEnemy.png"))
		return false;
	
	if (!backLineEnemyTexture.loadFromFile("Assets\\Sprites\\backLineEnemy.png"))
		return false;

	if (!enemyShotSoundBuffer.loadFromFile("Assets\\Sounds\\Shot02.ogg"))
		return false;
	
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\SpaceBackground.png"))
		return false;

	if (!bulletTexture.loadFromFile("Assets\\Sprites\\Bullet.png"))
		return false;

	if (!bonusTexture.loadFromFile("Assets\\Sprites\\Bonus.png"))
		return false;

	if (!bonusSoundBuffer.loadFromFile("Assets\\Sounds\\GameBonus.ogg"))
		return false;
	
	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
		return false;

	return true;
}

const sf::Texture& GameContentManager::getPlayerAnimationTexture() const
{
	return playerAnimationTexture;
}

const sf::SoundBuffer& GameContentManager::getPlayerShotSoundBuffer() const
{
	return playerShotSoundBuffer;
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

const sf::SoundBuffer& GameContentManager::getEnemyShotSoundBuffer() const
{
	return enemyShotSoundBuffer;
}

const sf::Texture& GameContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}

const sf::Texture& GameContentManager::getBulletTexture() const
{
	return bulletTexture;
}

const sf::Texture& GameContentManager::getBonusTexture() const
{
	return bonusTexture;
}

const sf::SoundBuffer& GameContentManager::getBonusSoundBuffer() const
{
	return bonusSoundBuffer;
}

const sf::Font& GameContentManager::getFont() const
{
	return font;
}

GameContentManager::GameContentManager()
: ContentManager()
{
}