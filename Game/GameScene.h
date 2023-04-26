#pragma once
#include "Scene.h"
#include "Pokeball.h"
#include "Pokemon.h"
#include "GameContentManager.h"
class GameScene :
  public Scene
{
public:
  static const float TIME_PER_FRAME;
public:
  GameScene();
  ~GameScene();
  virtual SceneType update() override;
  virtual void pause()override;
  virtual void unPause() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
private:
  sf::Vector2f pokeballTargetPosition;
  float remainingTimeInGame;

  int score;
  GameContentManager contentManager;

  Pokemon bulbasaur;
  Pokeball pokeball;

  sf::Text scoreText;
  sf::Text timeText;

  bool wentToEndScene = false;
};

