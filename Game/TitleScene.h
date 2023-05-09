#pragma once
#include "Scene.h"
#include "TitleContentManager.h"

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();
	virtual SceneType update() override;
	virtual void pause()override;
	virtual void unPause() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
	
private:
	TitleContentManager contentManager;

	bool shouldStartGame = false;

	sf::Text startGameText;
	sf::Text startGameCheatText;
	sf::Text escapeText;
	sf::Sprite background;
	sf::Sprite logo;
	sf::Music titleMusic;
};