#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "Animation.h"

AnimatedGameObject::AnimatedGameObject() : currentState(State::NONE)
    , contentManager(nullptr)
{
}
AnimatedGameObject::~AnimatedGameObject()
{
    for (auto const& anim : animations)
    {
        delete anim.second;
    }
    animations.clear();
}

AnimatedGameObject::AnimatedGameObject(const AnimatedGameObject& src)
    :GameObject(src), contentManager(src.contentManager)
{
}

void AnimatedGameObject::draw(sf::RenderWindow& window) const
{
    if (isActive())
        window.draw(*this);
}

bool AnimatedGameObject::update(float deltaT, const Inputs& inputs)
{
    bool retval = GameObject::update(deltaT);
    if (false == retval)
        animations[currentState]->update(deltaT, inputs);
    return retval;
}

bool AnimatedGameObject::init(const ContentManager& contentManager)
{
    this->contentManager = const_cast<ContentManager*>(&contentManager);
    return true;
}

void AnimatedGameObject::activate()
{
    for (auto const& anim : animations)
    {
        anim.second->reset();
    }
    GameObject::activate();
}
