#include "stdafx.h"
#include "GameHud.h"
#include "ContentManager.h"
#include "game.h"

const int GameHud::TXT_CHAR_SIZE = 40;
const int GameHud::GAP_FROM_BORDER = 10;

GameHud::GameHud()
{
}

void GameHud::initialize(const GameContentManager& contentManager)
{
	//const std::string introductionText = "Good luck!";
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));

	scoreTxt.setFont(contentManager.getFont());
	scoreTxt.setOutlineColor(sf::Color::White);
	scoreTxt.setCharacterSize(TXT_CHAR_SIZE);
	scoreTxt.setPosition(GAP_FROM_BORDER, GAP_FROM_BORDER);

	lifeTxt.setFont(contentManager.getFont());
	lifeTxt.setOutlineColor(sf::Color::White);
	lifeTxt.setCharacterSize(TXT_CHAR_SIZE);
	lifeTxt.setPosition(GAP_FROM_BORDER, Game::GAME_HEIGHT - (GAP_FROM_BORDER + TXT_CHAR_SIZE));
}

void GameHud::draw(sf::RenderWindow& window)  const
{
	window.setView(hudView);
	window.draw(scoreTxt);
	window.draw(lifeTxt);
}

void GameHud::setText(int score, int lifeLeft)
{
	scoreTxt.setString("Score : " + std::to_string(score));
	lifeTxt.setString("Lives : " + std::to_string(lifeLeft));
}