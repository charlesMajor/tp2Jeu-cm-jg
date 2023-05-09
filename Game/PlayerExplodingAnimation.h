#pragma once
#include "LinearAnimation.h"

class PlayerExplodingAnimation :
    public LinearAnimation
{
public:
    static const float ANIMATION_LENGTH;

    PlayerExplodingAnimation(sf::Sprite& s);
    virtual bool init(const ContentManager& contentManager) override;
};