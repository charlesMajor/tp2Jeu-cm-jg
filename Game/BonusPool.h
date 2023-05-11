#pragma once
#include "stdafx.h"
#include "Pool.h"

template<typename T>
class BonusPool : public Pool<T>
{
public:
	BonusPool();
	void init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb);

private:
	void createNewObject() override;
	sf::Texture texture;
	sf::Vector2f initialPosition;
	sf::SoundBuffer sb;
};

template<class T>
BonusPool<T>::BonusPool()
{
}

template<class T>
void BonusPool<T>::init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	this->texture = texture;
	this->initialPosition = initialPosition;
	this->sb = sb;

	for (int i = 0; i < nbObject; i++)
	{
		this->createNewObject();
	}
}

template<class T>
void BonusPool<T>::createNewObject()
{
	T obj;
	obj.initialize(texture, initialPosition);
	obj.setBonusBuffer(sb);
	Pool<T>::getPool().push_back(obj);
}