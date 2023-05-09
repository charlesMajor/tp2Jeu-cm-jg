#pragma once
#include "Scene.h"
#include "Enemy.h"
#include "FrontLineEnemy.h"
#include "AttackEnemy.h"
#include "BackLineEnemy.h"
#include "Player.h"
#include "GameContentManager.h"
#include "GameHud.h"
#include "Inputs.h"
#include "Bullet.h"

class GameScene :
  public Scene
{
public:
  static const float TIME_PER_FRAME;
  static const float KEYBOARD_SPEED;
  static const float GAMEPAD_SPEEDRATIO;
  static const int CONTROLLER_DEAD_ZONE;
  static const int MAX_RECOIL;
  static const int NB_BULLETS;

  static const int AMOUNT_FRONT_ENEMIES;
  static const int AMOUNT_FRONT_ENEMIES_POOL;
  static const int AMOUNT_ATTACK_ENEMIES;
  static const int AMOUNT_ATTACK_ENEMIES_POOL;
  static const int AMOUNT_BACK_ENEMIES;
  static const int AMOUNT_BACK_ENEMIES_POOL;

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
  GameContentManager contentManager;
  GameHud hud;

  float remainingTimeInGame;

  sf::Sprite backgroundSprite;
  sf::Music gameMusic;

  std::list<FrontLineEnemy> frontLineEnemyPool;
  std::list<AttackEnemy> attackEnemyPool;
  std::list<BackLineEnemy> backLineEnemyPool;

  int score;
  Inputs inputs;
  float handleControllerDeadZone(float analogInput);

  Player player;
  std::list<Bullet> playerBullets;
  int recoil = 0;
  void createNewBullet();
  void fireBullet(Bullet& bullet);
  Bullet& getAvaiableBullet();
  
  void initEnemiesPool();
  FrontLineEnemy& getAvailableFrontLineEnemy();
  AttackEnemy& getAvailableAttackEnemy();
  BackLineEnemy& getAvailableBackLineEnemy();
  std::list<Bullet> enemyBullets;

  bool wentToEndScene = false;
};