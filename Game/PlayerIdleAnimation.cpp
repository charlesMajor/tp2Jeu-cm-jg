#include "stdafx.h"
#include "PlayerIdleAnimation.h"
#include "ContentManager.h"
#include "GameContentManager.h"

const float PlayerIdleAnimation::ANIMATION_LENGTH = 1.5f;

PlayerIdleAnimation::PlayerIdleAnimation(sf::Sprite& s)
	: LinearAnimation(s, ANIMATION_LENGTH)
{
}

bool PlayerIdleAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = (GameContentManager&)contentManager;
	const sf::Texture& texture = gameContentManager.getPlayerAnimationTexture();

	frames.push_back(AnimationFrame(texture, sf::IntRect(0, 0, 62, 68)));

	return true;
}