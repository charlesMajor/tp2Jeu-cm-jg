#include "stdafx.h"
#include "PlayerExplodingAnimation.h"
#include "ContentManager.h"
#include "GameContentManager.h"

const float PlayerExplodingAnimation::ANIMATION_LENGTH = 0.75f;

PlayerExplodingAnimation::PlayerExplodingAnimation(sf::Sprite& s)
	: LinearAnimation(s, ANIMATION_LENGTH)
{
}

bool PlayerExplodingAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = (GameContentManager&)contentManager;
	const sf::Texture& texture = gameContentManager.getPlayerAnimationTexture();

	frames.push_back(AnimationFrame(texture, sf::IntRect(0, 328, 62, 57)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(63, 328, 62, 57)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(126, 328, 62, 57)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(189, 327, 63, 63)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(253, 327, 63, 63)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(317, 328, 61, 62)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(379, 326, 62, 61)));

	return true;
}