#pragma once
#include "LinearAnimation.h"

class PlayerIdleAnimation :
    public LinearAnimation
{
public:
    static const float ANIMATION_LENGTH;

    PlayerIdleAnimation(sf::Sprite& s);
    virtual bool init(const ContentManager& contentManager) override;
};