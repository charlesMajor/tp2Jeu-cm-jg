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
#include "Bonus.h"
#include "BulletPool.h"
#include "EnemyPool.h"
#include "BonusPool.h"
#include "Subscriber.h"

class GameScene :
  public Scene,
  public Subscriber
{
public:
  static const float TIME_PER_FRAME;
  static const float KEYBOARD_SPEED;
  static const float GAMEPAD_SPEEDRATIO;
  static const int CONTROLLER_DEAD_ZONE;

  static const int MAX_RECOIL;
  static const int NB_BULLETS;
  static const int NB_BONUS;
  static const int CHANCE_OF_BONUS;
  static const int SCORE_PER_SECOND;

  static const int PLAYER_BULLET_DIRECTION;
  static const int ENEMY_BULLET_DIRECTION;
  static const int BONUS_DIRECTION;

  static const int AMOUNT_FRONT_ENEMIES;
  static const int AMOUNT_FRONT_ENEMIES_POOL;
  static const int FRONT_ENEMIES_Y_POSITION;

  static const int AMOUNT_ATTACK_ENEMIES;
  static const int AMOUNT_ATTACK_ENEMIES_POOL;
  static const int ATTACK_ENEMIES_Y_POSITION;

  static const int AMOUNT_BACK_ENEMIES;
  static const int AMOUNT_BACK_ENEMIES_POOL;
  static const int BACK_ENEMIES_Y_POSITION;

  GameScene();
  ~GameScene();
  virtual SceneType update() override;
  virtual void pause()override;
  virtual void unPause() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
  void notify(Event event, const void* data) override;

private:
  GameContentManager contentManager;
  GameHud hud;

  sf::Sprite backgroundSprite;
  sf::Music gameMusic;
  sf::Sound enemyDeathSound;
  sf::Sound bonusAcquiredSound;

  EnemyPool<FrontLineEnemy> frontLineEnemyPool;
  EnemyPool<AttackEnemy> attackEnemyPool;
  EnemyPool<BackLineEnemy> backLineEnemyPool;

  BulletPool<Bullet> playerBullets;
  BulletPool<Bullet> enemyBullets;

  BonusPool<Bonus> bonusPool;

  Inputs inputs;
  Player player;

  void updateEnemies();
  float handleControllerDeadZone(float analogInput);
  void checkBulletCollisionWithEnemy(Bullet& bullet);
  void onbulletCollidesWithEnemy(Bullet& bullet, Enemy& enemy);
  void fireBullet(Bullet& bullet, GameObject from, int angle);
  void enemyDeathBonus(Enemy& enemy);

  int score;
  int recoil = 0;
  bool goToEndScene;
  bool wentToEndScene;
  float remainingTimeInGame;
  bool isInvincible;
};