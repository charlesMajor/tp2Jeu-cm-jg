#pragma once
#include "AnimationFrame.h"
<<<<<<< HEAD
struct Inputs;
class ContentManager;
=======

struct Inputs;
class ContentManager;

>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
class Animation
{
public:
	void reset();
	virtual void update(float deltaT, const Inputs& inputs);
	virtual unsigned int getNextFrame() const = 0;
	virtual bool init(const ContentManager& contentManager) = 0;
	float getTimeInCurrentState() const;
	virtual bool isOver() const;
	virtual float getPercentage() const = 0;
<<<<<<< HEAD
protected:

=======

protected:
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
	Animation(sf::Sprite& s, float length);
	std::vector<AnimationFrame> frames;
	float lengthInSeconds;
	float timeInCurrentState;

private:
	sf::Sprite& sprite;
<<<<<<< HEAD
};

=======
};
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
