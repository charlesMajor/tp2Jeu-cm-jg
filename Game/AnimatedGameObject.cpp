#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "Animation.h"

<<<<<<< HEAD
AnimatedGameObject::AnimatedGameObject()
    : currentState(State::NONE)
=======
AnimatedGameObject::AnimatedGameObject() : currentState(State::NONE)
>>>>>>> main
    , contentManager(nullptr)
{
}

<<<<<<< HEAD
}
=======
>>>>>>> main
AnimatedGameObject::~AnimatedGameObject()
{
    for (auto const& anim : animations)
    {
        delete anim.second;
    }
    animations.clear();
}
<<<<<<< HEAD

AnimatedGameObject::AnimatedGameObject(const AnimatedGameObject& src)
    :GameObject(src)
    , contentManager(src.contentManager)
{

=======
AnimatedGameObject::AnimatedGameObject(const AnimatedGameObject& src)
    :GameObject(src), contentManager(src.contentManager)
{
>>>>>>> main
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
<<<<<<< HEAD


=======
>>>>>>> main
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
<<<<<<< HEAD
}
=======
}
>>>>>>> main
