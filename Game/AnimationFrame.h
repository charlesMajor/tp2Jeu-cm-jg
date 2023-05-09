#pragma once
<<<<<<< HEAD
class AnimationFrame
{

=======

class AnimationFrame
{
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
public:
	AnimationFrame(const sf::Texture& text, sf::IntRect rect = sf::IntRect());
	const sf::Texture& getTexture() const;
	const sf::IntRect& getRectangle() const;
<<<<<<< HEAD
private:
	const sf::Texture& texture;
	sf::IntRect rectangle;
};

=======

private:
	const sf::Texture& texture;
	sf::IntRect rectangle;
};
>>>>>>> 649d856d8c9f5154b8109d6952eec4fac508ec81
