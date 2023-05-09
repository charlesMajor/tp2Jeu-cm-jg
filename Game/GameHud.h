#pragma once
#include <iostream>
#include "GameContentManager.h"

class ContentManager;
class GameHud
{
	static const int TXT_CHAR_SIZE;
	static const int GAP_FROM_BORDER;

public:
	GameHud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const GameContentManager& contentManager);
	void setText(int score, int lifeLeft);

private:
	sf::View hudView;

	sf::Text scoreTxt;
	sf::Text lifeTxt;
};