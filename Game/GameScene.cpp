#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include <iostream>

const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;

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
  if (remainingTimeInGame > 0)
  {
    bulbasaur.update(TIME_PER_FRAME);
    pokeball.update(TIME_PER_FRAME, pokeballTargetPosition);



    if (bulbasaur.collidesWith(pokeball))
    {
      score++;
      pokeball.stop();
      bulbasaur.onCatched();
    }

    scoreText.setString("Score: " + std::to_string(score));
    timeText.setString("Temps: " + std::to_string((int)(remainingTimeInGame)));
  }
  
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
  bulbasaur.draw(window);
  pokeball.draw(window);
  window.draw(scoreText);
  window.draw(timeText);
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
  sf::Vector2f pokeballInitialPosition((float)contentManager.getPokeballTexture().getSize().x,
    (float)contentManager.getPokeballTexture().getSize().y);
  pokeball.initialize(contentManager.getPokeballTexture(), pokeballInitialPosition);
  pokeballTargetPosition = pokeballInitialPosition;

  bulbasaur.initialize(contentManager.getBulbasaurTexture(), sf::Vector2f(Game::GAME_WIDTH - 100.0f, Game::GAME_HEIGHT - 100.0f));
  bulbasaur.loadPokemonSpeaks(contentManager.getBulbasaurSoundBuffer());

  scoreText.setFont(contentManager.getFont());
  scoreText.setCharacterSize(50);
  scoreText.setOutlineColor(sf::Color::White);
  scoreText.setPosition(10, 10);

  timeText.setFont(contentManager.getFont());
  timeText.setCharacterSize(50);
  timeText.setOutlineColor(sf::Color::White);
  timeText.setPosition(800, 10);
  
  remainingTimeInGame = (float)Game::DEFAULT_GAME_TIME;
  if (this->result.titleSceneResult.isLongGame == false)
  {
      remainingTimeInGame = (float)Game::SHORT_GAME_TIME;
  }

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
