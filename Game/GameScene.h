#pragma once
#include "Scene.h"
#include "Pokeball.h"
#include "Enemy.h"
#include "FrontLineEnemy.h"
#include "AttackEnemy.h"
#include "BackLineEnemy.h"
#include "GameContentManager.h"
#include "Bullet.h"

class GameScene :
  public Scene
{
public:
  static const float TIME_PER_FRAME;
  static const int AMOUNT_FRONT_ENEMIES;
  static const int AMOUNT_FRONT_ENEMIES_POOL;
  static const int AMOUNT_ATTACK_ENEMIES;
  static const int AMOUNT_ATTACK_ENEMIES_POOL;
  static const int AMOUNT_BACK_ENEMIES;
  static const int AMOUNT_BACK_ENEMIES_POOL;
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
	void initEnemiesPool();
	FrontLineEnemy& getAvailableFrontLineEnemy();
	AttackEnemy& getAvailableAttackEnemy();
	BackLineEnemy& getAvailableBackLineEnemy();

  sf::Vector2f pokeballTargetPosition;
  float remainingTimeInGame;

  int score;
  GameContentManager contentManager;

  std::list<Bullet> bulletPool;
  std::list<FrontLineEnemy> frontLineEnemyPool;
  std::list<AttackEnemy> attackEnemyPool;
  std::list<BackLineEnemy> backLineEnemyPool;

  sf::Text scoreText;
  sf::Text timeText;

  bool wentToEndScene = false;
};

