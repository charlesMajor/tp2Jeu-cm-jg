#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include <iostream>

const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const int GameScene::AMOUNT_FRONT_ENEMIES = 6;
const int GameScene::AMOUNT_FRONT_ENEMIES_POOL = GameScene::AMOUNT_FRONT_ENEMIES + 2;
const int GameScene::AMOUNT_ATTACK_ENEMIES = 10;
const int GameScene::AMOUNT_ATTACK_ENEMIES_POOL = GameScene::AMOUNT_ATTACK_ENEMIES + 2;
const int GameScene::AMOUNT_BACK_ENEMIES = 6;
const int GameScene::AMOUNT_BACK_ENEMIES_POOL = GameScene::AMOUNT_BACK_ENEMIES + 2;

GameScene::GameScene()
  : Scene(SceneType::GAME_SCENE)
{
}

GameScene::~GameScene()
{

}

SceneType GameScene::update()
{
  SceneType retval = getSceneType();

  if (wentToEndScene)
  {
      return SceneType::NONE;
  }
  
  remainingTimeInGame -= TIME_PER_FRAME;
  
  if (remainingTimeInGame <= 0)
  {
      this->wentToEndScene = true;
      this->result.gameSceneResult.score = score;
      retval = SceneType::END_SCENE;
  }

  return retval;
}

void GameScene::pause()
{

}

void GameScene::unPause()
{

}

void GameScene::draw(sf::RenderWindow& window) const
{
  for (const Enemy& current : frontLineEnemyPool)
  {
      if (current.isActive())
      {
          current.draw(window);
      }
  }

  for (const Enemy& current : attackEnemyPool)
  {
      if (current.isActive())
      {
          current.draw(window);
      }
  }

  for (const Enemy& current : backLineEnemyPool)
  {
      if (current.isActive())
      {
          current.draw(window);
      }
  }
}

bool GameScene::uninit()
{
  return true;
}

bool GameScene::init()
{
  if (contentManager.loadContent() == false)
  {
    return false;
  }
 
  srand((unsigned)time(NULL));

  initEnemiesPool();

  for (int i = 0; i < GameScene::AMOUNT_FRONT_ENEMIES; i++)
  {
      FrontLineEnemy& enemy = getAvailableFrontLineEnemy();
      enemy.setPosition(i*100 + 75, 455);
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES; i++)
  {
      AttackEnemy& enemy = getAvailableAttackEnemy();
      if (i <= 4)
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

  remainingTimeInGame = (float)Game::DEFAULT_GAME_TIME;
  std::cout << "invincible: " << this->result.titleSceneResult.isInvincible << std::endl;
  
  score = 0;
  return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        pokeballTargetPosition = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
      }
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
        {
            return enemy;
        }
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
        {
            return enemy;
        }
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
        {
            return enemy;
        }
    }

    BackLineEnemy newEnemy = BackLineEnemy();
    newEnemy.initialize(contentManager, sf::Vector2f(0, 0));
    backLineEnemyPool.push_back(newEnemy);
    return backLineEnemyPool.back();
}
