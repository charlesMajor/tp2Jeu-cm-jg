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
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));

	scoreTxt.setFont(contentManager.getFont());
	scoreTxt.setOutlineColor(sf::Color::White);
	scoreTxt.setCharacterSize(TXT_CHAR_SIZE);
	scoreTxt.setPosition(GAP_FROM_BORDER, GAP_FROM_BORDER);

	lifeTxt.setFont(contentManager.getFont());
	lifeTxt.setOutlineColor(sf::Color::White);
	lifeTxt.setCharacterSize(TXT_CHAR_SIZE);
	lifeTxt.setPosition(GAP_FROM_BORDER, Game::GAME_HEIGHT - (GAP_FROM_BORDER + TXT_CHAR_SIZE));

	timeLeftTxt.setFont(contentManager.getFont());
	timeLeftTxt.setOutlineColor(sf::Color::White);
	timeLeftTxt.setCharacterSize(TXT_CHAR_SIZE);
	timeLeftTxt.setPosition(Game::GAME_WIDTH / 2 + GAP_FROM_BORDER * 4 + TXT_CHAR_SIZE, GAP_FROM_BORDER);
}

void GameHud::draw(sf::RenderWindow& window)  const
{
	window.setView(hudView);
	window.draw(scoreTxt);
	window.draw(lifeTxt);
	window.draw(timeLeftTxt);
}

void GameHud::setText(int score, int lifeLeft, float timeLeft)
{
	scoreTxt.setString("Score : " + std::to_string(score));
	lifeTxt.setString("Lives : " + std::to_string(lifeLeft));
	timeLeftTxt.setString("Time : " + std::to_string(timeLeft).substr(0, 5));
}