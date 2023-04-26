#pragma once
#include "stdafx.h"
#include "scenetype.h"

class Scene;
class Game
{
 typedef class Scene InitialScene;
 public:
   static const int WORLD_WIDTH;
   static const int WORLD_HEIGHT;
public:
  static const unsigned int DEFAULT_GAME_TIME;
  static const unsigned int SHORT_GAME_TIME;
  static const unsigned int FRAME_RATE;
  static const unsigned int GAME_WIDTH;
  static const unsigned int GAME_HEIGHT;

public:
  Game(std::string windowName);
  void run();

private:
  bool update();
  void draw(sf::RenderWindow& window) const;
  bool init();
  bool uninit();
  bool handleEvents();

  std::string gameName;
  sf::RenderWindow window;

  // Gestion des scènes
  Scene* getNextScene(SceneType type) const;
  bool popScene(bool initScene = true);
  bool pushScene(Scene* newScene);
  std::stack<Scene*> scenes;
};

