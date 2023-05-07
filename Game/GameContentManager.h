#pragma once
#include "ContentManager.h"
class GameContentManager : public ContentManager
{
public:
	GameContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getFrontLineEnemyTexture() const;
	const sf::Texture& getAttackEnemyTexture() const;
	const sf::Texture& getBackLineEnemyTexture() const;
	const sf::Font& getFont() const;

private:
	sf::Texture frontLineEnemyTexture;
	sf::Texture attackEnemyTexture;
	sf::Texture backLineEnemyTexture;
	sf::Font font;
};



