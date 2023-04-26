#pragma once

struct TitleSceneResult
{
	bool isInvincible;
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