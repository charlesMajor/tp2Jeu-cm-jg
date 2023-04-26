#pragma once
#include "Scene.h"
#include "TitleContentManager.h"
class TitleScene :
	public Scene
{
public:
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

	// ppoulin
	// shouldStartGame aurait été un meilleur nom
	// VAN-1
	bool buttonClicked = false;

	sf::Text longGameText;
	sf::Text shortGameText;
	sf::Sprite titleSprite;
	sf::Music titleMusic;
};

