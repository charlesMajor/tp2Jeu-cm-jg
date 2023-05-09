#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include <iostream>

const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float GameScene::KEYBOARD_SPEED = 5.0f;
const float GameScene::GAMEPAD_SPEEDRATIO = 50.0f;
const int GameScene::CONTROLLER_DEAD_ZONE = 20;

const int GameScene::MAX_RECOIL = 20;
const int GameScene::NB_BULLETS = 10;

const int GameScene::AMOUNT_FRONT_ENEMIES = 6;
const int GameScene::AMOUNT_FRONT_ENEMIES_POOL = GameScene::AMOUNT_FRONT_ENEMIES + 2;
const int GameScene::FRONT_ENEMIES_Y_POSITION = 455;

const int GameScene::AMOUNT_ATTACK_ENEMIES = 10;
const int GameScene::AMOUNT_ATTACK_ENEMIES_POOL = GameScene::AMOUNT_ATTACK_ENEMIES + 2;

const int GameScene::AMOUNT_BACK_ENEMIES = 6;
const int GameScene::AMOUNT_BACK_ENEMIES_POOL = GameScene::AMOUNT_BACK_ENEMIES + 2;

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
    recoil = std::max(0, recoil - 1);
    for (Bullet& bullet : playerBullets)
    {
        if (bullet.isActive())
        {
            bullet.update(TIME_PER_FRAME);
            /*for (Enemy& enemy : enemies)
            {
                if (bullet.collidesWith(enemy))
                {
                    enemy.deactivate();
                    bullet.deactivate();
                    this->createNewBonus(enemy);
                    this->addScore(ENEMY_KILL_SCORE);
                    hud.drawEnemyScore(window, window.mapPixelToCoords(sf::Vector2i(enemy.getPosition())));
                }
            }*/
        }
    }

    if (inputs.fireBullet)
        this->fireBullet(this->getAvaiableBullet());

    player.update(TIME_PER_FRAME, inputs);

    hud.setText(score, player.getLifeLeft());
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

  for (const Enemy& current : frontLineEnemyPool)
  {
      if (current.isActive())
          current.draw(window);
  }

  for (const Enemy& current : attackEnemyPool)
  {
      if (current.isActive())
          current.draw(window);
  }

  for (const Enemy& current : backLineEnemyPool)
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
 
  srand((unsigned)time(NULL)); //Utilitée ?

  initEnemiesPool();

  for (int i = 0; i < GameScene::AMOUNT_FRONT_ENEMIES; i++)
  {
      FrontLineEnemy& enemy = getAvailableFrontLineEnemy();
      enemy.setPosition(i*100 + 75, FRONT_ENEMIES_Y_POSITION);
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES; i++)
  {
      AttackEnemy& enemy = getAvailableAttackEnemy();
      if (i < (AMOUNT_ATTACK_ENEMIES / 2))
      {
          enemy.setPosition(i * 110 + 100, 225);
      }
      else
      {
          enemy.setPosition(i * 110 - 450, 325);
      }
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_BACK_ENEMIES; i++)
  {
      BackLineEnemy& enemy = getAvailableBackLineEnemy();
      enemy.setPosition(i * 100 + 70, 125);
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
        //inputs.moveFactor = -handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;
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
        this->frontLineEnemyPool.push_back(current);
    }

    for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES_POOL; i++)
    {
        AttackEnemy current;
        current.initialize(contentManager, sf::Vector2f(0, 0));
        this->attackEnemyPool.push_back(current);
    }

    for (int i = 0; i < AMOUNT_BACK_ENEMIES_POOL; i++)
    {
        BackLineEnemy current;
        current.initialize(contentManager, sf::Vector2f(0, 0));
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

    FrontLineEnemy newEnemy = FrontLineEnemy();
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
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

    AttackEnemy newEnemy = AttackEnemy();
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
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

    BackLineEnemy newEnemy = BackLineEnemy();
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
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

void GameScene::fireBullet(Bullet& bullet)
{
    bullet.setPosition(player.getPosition());
    bullet.setRotation(-90);
    bullet.activate();
    inputs.fireBullet = false;
    recoil = MAX_RECOIL;
}