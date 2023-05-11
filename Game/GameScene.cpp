#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include <iostream>

const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float GameScene::KEYBOARD_SPEED = 5.0f;
const float GameScene::GAMEPAD_SPEEDRATIO = 20.0f;
const int GameScene::CONTROLLER_DEAD_ZONE = 20;

const int GameScene::MAX_RECOIL = 20;
const int GameScene::NB_BULLETS = 10;

const int GameScene::AMOUNT_ENEMIES_POOL = GameScene::AMOUNT_FRONT_ENEMIES_POOL + GameScene::AMOUNT_ATTACK_ENEMIES_POOL + GameScene::AMOUNT_FRONT_ENEMIES_POOL;

const int GameScene::AMOUNT_FRONT_ENEMIES = 6;
const int GameScene::AMOUNT_FRONT_ENEMIES_POOL = GameScene::AMOUNT_FRONT_ENEMIES + 2;
const int GameScene::FRONT_ENEMIES_Y_POSITION = 455;

const int GameScene::AMOUNT_ATTACK_ENEMIES = 10;
const int GameScene::AMOUNT_ATTACK_ENEMIES_POOL = GameScene::AMOUNT_ATTACK_ENEMIES + 2;
const int GameScene::ATTACK_ENEMIES_Y_POSITION = 225;

const int GameScene::AMOUNT_BACK_ENEMIES = 6;
const int GameScene::AMOUNT_BACK_ENEMIES_POOL = GameScene::AMOUNT_BACK_ENEMIES + 2;
const int GameScene::BACK_ENEMIES_Y_POSITION = 125;

GameScene::GameScene()
  : Scene(SceneType::GAME_SCENE)
  , wentToEndScene(false)
  , score(0)
{
}

GameScene::~GameScene()
{
}

SceneType GameScene::update()
{
  static int cptScrollBackground = 0;
  backgroundSprite.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground++), Game::GAME_WIDTH, Game::GAME_HEIGHT));

  SceneType retval = getSceneType();
  
  remainingTimeInGame -= TIME_PER_FRAME;

  if (remainingTimeInGame > 0)
  {
      for (FrontLineEnemy& enemy : frontLineEnemyPool)
      {
          if (enemy.isActive())
          {
              enemy.update(TIME_PER_FRAME);
          }   
      }

      for (AttackEnemy& enemy : attackEnemyPool)
      {
          if (enemy.isActive())
          {
              if (enemy.update(TIME_PER_FRAME, player.getPosition()))
              {
                  this->fireBullet(this->getAvaiableBullet(), enemy, 90);
              }
          }
      }

      for (BackLineEnemy& enemy : backLineEnemyPool)
      {
          if (enemy.isActive())
          {
              enemy.update(TIME_PER_FRAME);
          }
      }

    for (Bullet& bullet : playerBullets)
    {
        if (bullet.isActive())
        {
            bullet.update(TIME_PER_FRAME);
            if (bullet.fromPlayer)
            {
                for (Enemy& enemy : frontLineEnemyPool)
                {
                    if (bullet.collidesWith(enemy))
                    {
                        bullet.deactivate();
                        enemy.onHit();
                        /*this->createNewBonus(enemy);
                        this->addScore(ENEMY_KILL_SCORE);
                        hud.drawEnemyScore(window, window.mapPixelToCoords(sf::Vector2i(enemy.getPosition())));*/
                    }
                }

                for (Enemy& enemy : attackEnemyPool)
                {
                    if (bullet.collidesWith(enemy))
                    {
                        bullet.deactivate();
                        enemy.onHit();
                        /*this->createNewBonus(enemy);
                        this->addScore(ENEMY_KILL_SCORE);
                        hud.drawEnemyScore(window, window.mapPixelToCoords(sf::Vector2i(enemy.getPosition())));*/
                    }
                }

                for (Enemy& enemy : backLineEnemyPool)
                {
                    if (bullet.collidesWith(enemy))
                    {
                        bullet.deactivate();
                        enemy.onHit();
                        /*this->createNewBonus(enemy);
                        this->addScore(ENEMY_KILL_SCORE);
                        hud.drawEnemyScore(window, window.mapPixelToCoords(sf::Vector2i(enemy.getPosition())));*/
                    }
                }
            }
            else
            {
                if (bullet.collidesWith(player))
                {
                    bullet.deactivate();
                    player.onHit();
                }
            }
        }
    }

    recoil = std::max(0, recoil - 1);
    if (inputs.fireBullet && recoil == 0)
        this->fireBullet(this->getAvaiableBullet(), player, -90);

    player.update(TIME_PER_FRAME, inputs);

    hud.setText(score, player.getLifeLeft(), remainingTimeInGame);
  }
  else {
      if (wentToEndScene) {
          retval = SceneType::NONE;
      }
      else {
          this->wentToEndScene = true;
          //this->result.gameSceneResult.score = score;
          retval = SceneType::END_SCENE;
      }
  }

  return retval;
}

void GameScene::pause()
{
    gameMusic.stop();
}

void GameScene::unPause()
{
    gameMusic.play();
}

void GameScene::draw(sf::RenderWindow& window) const
{
  window.draw(backgroundSprite);
  /*for (const Enemy& current : enemyPool)
  if (<FrontLineEnemy>()*/

  for (const FrontLineEnemy& current : frontLineEnemyPool)
  {
      if (current.isActive())
          current.draw(window);
  }

  for (const AttackEnemy& current : attackEnemyPool)
  {
      if (current.isActive())
          current.draw(window);
  }

  for (const BackLineEnemy& current : backLineEnemyPool)
  {
      if (current.isActive())
          current.draw(window);
  }

  for (const Bullet& bullet : playerBullets)
  {
      if (bullet.isActive())
          bullet.draw(window);
  }
  player.draw(window);

  hud.draw(window);
}

bool GameScene::uninit()
{
  return true;
}

bool GameScene::init()
{
  inputs.reset();
  recoil = MAX_RECOIL;

  if (contentManager.loadContent() == false)
  {
    return false;
  }
  
  backgroundSprite.setTexture(contentManager.getBackgroundTexture());

  player.init(contentManager);

  initEnemiesPool();

  for (int i = 0; i < GameScene::AMOUNT_FRONT_ENEMIES; i++)
  {
      FrontLineEnemy& enemy = getAvailableFrontLineEnemy();

      enemy.setPosition(i*110 + 75, FRONT_ENEMIES_Y_POSITION);
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES; i++)
  {
      AttackEnemy& enemy = getAvailableAttackEnemy();
      if (i < (AMOUNT_ATTACK_ENEMIES / 2))
      {
          enemy.setPosition(i * 115 + 125, ATTACK_ENEMIES_Y_POSITION);
      }
      else
      {
          enemy.setPosition(i * 115 - 450, ATTACK_ENEMIES_Y_POSITION + 100);
      }
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_BACK_ENEMIES; i++)
  {
      BackLineEnemy& enemy = getAvailableBackLineEnemy();

      enemy.setPosition(i * 110 + 80, BACK_ENEMIES_Y_POSITION);
      enemy.activate();
  }

  for (int i = 0; i < NB_BULLETS; i++)
  {
      this->createNewBullet();
  }
  
  remainingTimeInGame = (float)Game::DEFAULT_GAME_TIME;
  std::cout << "invincible: " << this->result.titleSceneResult.isInvincible << std::endl;

  hud.initialize(contentManager);

  if (!gameMusic.openFromFile("Assets\\Music\\GameTheme.ogg"))
      return false;
  gameMusic.setLoop(true);
  gameMusic.play();

  return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;

  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
    if (sf::Joystick::isConnected(0))
    {
        //TODO: Vérifier
        inputs.moveFactor = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;
        inputs.fireBullet = sf::Joystick::isButtonPressed(0, 0) && (recoil == 0);
    }
    else {
        inputs.moveFactor = 0.0f;
        inputs.moveFactor += sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -KEYBOARD_SPEED : 0.0f;
        inputs.moveFactor += sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? KEYBOARD_SPEED : 0.0f;
        inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (recoil == 0);
    }
  }
  return retval;
}

void GameScene::initEnemiesPool()
{
    for (int i = 0; i < GameScene::AMOUNT_FRONT_ENEMIES_POOL; i++)
    {
        FrontLineEnemy current;
        current.initialize(contentManager, sf::Vector2f(0, 0));
        current.deactivate();
        this->frontLineEnemyPool.push_back(current);
    }

    for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES_POOL; i++)
    {
        AttackEnemy current;
        current.initialize(contentManager, sf::Vector2f(0, 0));
        current.deactivate();
        this->attackEnemyPool.push_back(current);
    }

    for (int i = 0; i < AMOUNT_BACK_ENEMIES_POOL; i++)
    {
        BackLineEnemy current;
        current.initialize(contentManager, sf::Vector2f(0, 0));
        current.deactivate();
        this->backLineEnemyPool.push_back(current);
    }
}

FrontLineEnemy& GameScene::getAvailableFrontLineEnemy()
{
    for (FrontLineEnemy& enemy : frontLineEnemyPool)
    {
        if (!enemy.isActive())
            return enemy;
    }

    FrontLineEnemy newEnemy;
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
    newEnemy.deactivate();
    frontLineEnemyPool.push_back(newEnemy);
    return frontLineEnemyPool.back();
}

AttackEnemy& GameScene::getAvailableAttackEnemy()
{
    for (AttackEnemy& enemy : attackEnemyPool)
    {
        if (!enemy.isActive())
            return enemy;
    }

    AttackEnemy newEnemy;
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
    newEnemy.deactivate();
    attackEnemyPool.push_back(newEnemy);
    return attackEnemyPool.back();

    return newEnemy;
}

BackLineEnemy& GameScene::getAvailableBackLineEnemy()
{
    for (BackLineEnemy& enemy : backLineEnemyPool)
    {
        if (!enemy.isActive())
            return enemy;
    }

    BackLineEnemy newEnemy;
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
    newEnemy.deactivate();
    backLineEnemyPool.push_back(newEnemy);
    return backLineEnemyPool.back();
}

float GameScene::handleControllerDeadZone(float analogInput)
{
    if (fabs(analogInput) < CONTROLLER_DEAD_ZONE)
    {
        analogInput = 0.0f;
    }
    return analogInput;
}

Bullet& GameScene::getAvaiableBullet()
{
    for (Bullet& bullet : playerBullets)
    {
        if (!bullet.isActive())
            return bullet;
    }
    this->createNewBullet();
    return playerBullets.back();
}

void GameScene::createNewBullet()
{
    Bullet bullet;
    bullet.initialize(contentManager.getBulletTexture(), sf::Vector2f(0, 0), contentManager.getPlayerShotSoundBuffer());
    playerBullets.push_back(bullet);
}

void GameScene::fireBullet(Bullet& bullet, GameObject from, int angle)
{
    bullet.setPosition(from.getPosition());
    if (from.getPosition().y >= FRONT_ENEMIES_Y_POSITION)
    {
        bullet.setRotation(angle);
        bullet.setColor(sf::Color::White);
        bullet.fromPlayer = true;
        inputs.fireBullet = false;
        recoil = MAX_RECOIL;
    }
    else
    {
        bullet.setRotation(angle);
        bullet.setColor(sf::Color::Red);
        bullet.fromPlayer = false;
    }
    bullet.activate();
}