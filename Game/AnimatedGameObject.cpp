#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "Animation.h"

AnimatedGameObject::AnimatedGameObject()
    : currentState(State::NONE)
    , contentManager(nullptr)
{
<<<<<<< HEAD

}
=======
}

>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
AnimatedGameObject::~AnimatedGameObject()
{
    for (auto const& anim : animations)
    {
        delete anim.second;
    }
    animations.clear();
}
<<<<<<< HEAD
=======

>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
AnimatedGameObject::AnimatedGameObject(const AnimatedGameObject& src)
    :GameObject(src)
    , contentManager(src.contentManager)
{
<<<<<<< HEAD

}
=======
}

>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
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
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
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
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
