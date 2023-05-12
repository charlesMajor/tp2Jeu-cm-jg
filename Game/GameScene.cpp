#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include "Publisher.h"
#include "EnemyDeathData.h"
#include <iostream>

const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float GameScene::KEYBOARD_SPEED = 5.0f;
const float GameScene::GAMEPAD_SPEEDRATIO = 20.0f;
const int GameScene::CONTROLLER_DEAD_ZONE = 20;

const int GameScene::MAX_RECOIL = 20;
const int GameScene::NB_BULLETS = 20;
const int GameScene::NB_BONUS = 3;
const int GameScene::CHANCE_OF_BONUS = 5;
const int GameScene::SCORE_PER_SECOND = 20;

const int GameScene::PLAYER_BULLET_DIRECTION = -90;
const int GameScene::ENEMY_BULLET_DIRECTION = 90;
const int GameScene::BONUS_DIRECTION = 90;

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
  , remainingTimeInGame(Game::DEFAULT_GAME_TIME)
  , isInvincible(false)
  , goToEndScene(false)
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

  if (remainingTimeInGame > 0 && !goToEndScene)
  {
    updateEnemies();

    for (Bullet& bullet : playerBullets.getPool())
    {
        if (bullet.isActive())
        {
            bullet.update(TIME_PER_FRAME);
            checkBulletCollisionWithEnemy(bullet);
        }
    }

    for (Bullet& bullet : enemyBullets.getPool())
    {
        if (bullet.isActive())
        {
            bullet.update(TIME_PER_FRAME);
            if (!isInvincible)
            {
                if (bullet.collidesWith(player))
                {
                    bullet.deactivate();
                    player.onHit();
                }
            }
        }
    }

    for (Bonus& bonus : bonusPool.getPool())
    {
        if (bonus.isActive())
        {
            bonus.update(TIME_PER_FRAME);

            if (bonus.collidesWith(player))
                bonus.deactivate();
        }
    }

    recoil = std::max(0, recoil - 1);
    if (inputs.fireBullet && recoil == 0)
        this->fireBullet(playerBullets.getAvaiableObject(), player, PLAYER_BULLET_DIRECTION);

    player.update(TIME_PER_FRAME, inputs);

    hud.setText(score, player.getLifeLeft(), remainingTimeInGame);
  }
  else {
        if (wentToEndScene) {
            retval = SceneType::NONE;
        }
        else {
            this->wentToEndScene = true;
            this->result.gameSceneResult.score = score;
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

  frontLineEnemyPool.draw(window);
  attackEnemyPool.draw(window);
  backLineEnemyPool.draw(window);
  playerBullets.draw(window);
  enemyBullets.draw(window);
  bonusPool.draw(window);

  player.draw(window);

  hud.draw(window);
}

bool GameScene::uninit()
{
  Publisher::removeSubscriber(*this, Event::ENEMY_DEATH);
  Publisher::removeSubscriber(*this, Event::BONUS_ACQUIRED);
  Publisher::removeSubscriber(*this, Event::PLAYER_DEATH);
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
  enemyDeathSound.setBuffer(contentManager.getEnemyDeathSoundBuffer());
  bonusAcquiredSound.setBuffer(contentManager.getBonusSoundBuffer());

  player.init(contentManager);
 
  srand((unsigned)time(NULL));

  frontLineEnemyPool.init(AMOUNT_FRONT_ENEMIES_POOL, contentManager.getFrontLineEnemyTexture(), sf::Vector2f(0, 0));
  attackEnemyPool.init(AMOUNT_ATTACK_ENEMIES_POOL, contentManager.getAttackEnemyTexture(), sf::Vector2f(0, 0));
  backLineEnemyPool.init(AMOUNT_BACK_ENEMIES_POOL, contentManager.getBackLineEnemyTexture(), sf::Vector2f(0, 0));

  for (int i = 0; i < GameScene::AMOUNT_FRONT_ENEMIES; i++)
  {
      FrontLineEnemy& enemy = frontLineEnemyPool.getAvaiableObject();
      enemy.setPosition(i * 110 + 75, FRONT_ENEMIES_Y_POSITION);
      enemy.activate();
  }

  for (int i = 0; i < GameScene::AMOUNT_ATTACK_ENEMIES; i++)
  {
      AttackEnemy& enemy = attackEnemyPool.getAvaiableObject();
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
      BackLineEnemy& enemy = backLineEnemyPool.getAvaiableObject();
      enemy.setPosition(i * 110 + 80, BACK_ENEMIES_Y_POSITION);
      enemy.activate();
  }

  playerBullets.init(NB_BULLETS, contentManager.getBulletTexture(), sf::Vector2f(0, 0), contentManager.getPlayerShotSoundBuffer());
  enemyBullets.init(NB_BULLETS, contentManager.getBulletTexture(), sf::Vector2f(0, 0), contentManager.getEnemyShotSoundBuffer());
  bonusPool.init(NB_BONUS, contentManager.getBonusTexture(), sf::Vector2f(0, 0));
  
  remainingTimeInGame = (float)Game::DEFAULT_GAME_TIME;
  isInvincible = this->result.titleSceneResult.isInvincible;

  Publisher::addSubscriber(*this, Event::ENEMY_DEATH);
  Publisher::addSubscriber(*this, Event::BONUS_ACQUIRED);
  Publisher::addSubscriber(*this, Event::PLAYER_DEATH);

  hud.initialize(contentManager);

  if (!gameMusic.openFromFile("Assets\\Sounds\\gameMusic.ogg"))
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

float GameScene::handleControllerDeadZone(float analogInput)
{
    if (fabs(analogInput) < CONTROLLER_DEAD_ZONE)
    {
        analogInput = 0.0f;
    }
    return analogInput;
}

void GameScene::fireBullet(Bullet& bullet, GameObject from, int angle)
{
    bullet.setPosition(from.getPosition());
    if (from.getPosition().y >= FRONT_ENEMIES_Y_POSITION)
    {
        bullet.setRotation(angle);
        bullet.setColor(sf::Color::White);
        inputs.fireBullet = false;
        recoil = MAX_RECOIL;
    }
    else
    {
        bullet.setRotation(angle);
        bullet.setColor(sf::Color::Red);
    }
    bullet.activate();
}

void GameScene::updateEnemies()
{
    for (FrontLineEnemy& enemy : frontLineEnemyPool.getPool())
    {
        if (enemy.isActive())
        {
            enemy.update(TIME_PER_FRAME);
        }
    }

    for (AttackEnemy& enemy : attackEnemyPool.getPool())
    {
        if (enemy.isActive())
        {
            if (enemy.update(TIME_PER_FRAME, player.getPosition()))
            {
                this->fireBullet(enemyBullets.getAvaiableObject(), enemy, ENEMY_BULLET_DIRECTION);
            }
        }
    }

    int amountBackEnemies = 0;
    for (BackLineEnemy& enemy : backLineEnemyPool.getPool())
    {
        if (enemy.isActive())
        {
            if (enemy.update(TIME_PER_FRAME, score, player.isSlowed()))
            {
                amountBackEnemies++;
            }
        }
    }
    player.slow(amountBackEnemies);
}

void GameScene::checkBulletCollisionWithEnemy(Bullet& bullet)
{
    for (Enemy& enemy : frontLineEnemyPool.getPool())
    {
        if (bullet.collidesWith(enemy))
        {
            onbulletCollidesWithEnemy(bullet, enemy);
        }
    }

    for (Enemy& enemy : attackEnemyPool.getPool())
    {
        if (bullet.collidesWith(enemy))
        {
            onbulletCollidesWithEnemy(bullet, enemy);
        }
    }

    for (Enemy& enemy : backLineEnemyPool.getPool())
    {
        if (bullet.collidesWith(enemy))
        {
            onbulletCollidesWithEnemy(bullet, enemy);
        }
    }
}

void GameScene::onbulletCollidesWithEnemy(Bullet& bullet, Enemy& enemy)
{
    bullet.deactivate();
    enemy.onHit();
}

void GameScene::notify(Event event, const void* data)
{
    EnemyDeathData* enemyDeathData;

    int timeScore;

    switch (event)
    {
    case Event::ENEMY_DEATH:
        enemyDeathData = (EnemyDeathData*)data;
        score += enemyDeathData->score;

        enemyDeathBonus(*enemyDeathData->enemy);

        enemyDeathSound.play();

        break;
    case Event::BONUS_ACQUIRED:
        player.addOneLife();
        score += Bonus::BONUS_SCORE;

        bonusAcquiredSound.play();

        break;
    case Event::PLAYER_DEATH:
        goToEndScene = true;

        break;
    default:
        break;
    }
}

void GameScene::enemyDeathBonus(Enemy& enemy)
{
    if (std::rand() % CHANCE_OF_BONUS + 1 == 1)
    {
        Bonus& bonus = bonusPool.getAvaiableObject();
        bonus.setPosition(enemy.getPosition());
        bonus.setRotation(BONUS_DIRECTION);
        bonus.activate();
    }
}