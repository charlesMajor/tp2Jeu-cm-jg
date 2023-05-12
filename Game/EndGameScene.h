#pragma once
#include "Scene.h"
#include "EndGameContentManager.h"
#include "Score.h"

class EndGameScene :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
	static const int AMOUNT_IN_LEADERBOARD;
public:
	EndGameScene();
	~EndGameScene();
	virtual SceneType update() override;
	virtual void pause()override;
	virtual void unPause() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
	void serializeTab();
	bool unserializeTab();
	void replaceIfBetter();
private:
	EndGameContentManager contentManager;

	Score baseTable[5];
	Score newTable[5];

	sf::Text gameOverText;
	sf::Text leaderboardText;
	sf::Text backToTitleText;
	sf::Text nomText;
	sf::Music endMusic;

	std::list<sf::Text> bestPlayers;
	std::list<sf::Text> bestScores;

	int playerScore;

	bool drawNomText = false;
	bool needsToEnterName = false;
	int changeNomTextState = 30;
	int placeInLeaderBoard;
	bool backToTitle = false;
};

