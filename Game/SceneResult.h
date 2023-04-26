#pragma once

struct TitleSceneResult
{
  bool isLongGame;
};

struct GameSceneResult
{
	int score;
};

union SceneResult
{
  TitleSceneResult titleSceneResult;
  GameSceneResult gameSceneResult;
};