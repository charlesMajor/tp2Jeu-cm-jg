#pragma once
#include "Scene.h"
#include "EndGameContentManager.h"
class EndGameScene :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
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
private:
	EndGameContentManager contentManager;

	sf::Text gameOverText;
	sf::Text backToTitleText;
	sf::Sprite endSprite;
	sf::Music endMusic;

	bool backToTitle = false;
};

