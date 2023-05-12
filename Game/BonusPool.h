#pragma once
#include "stdafx.h"
#include "Pool.h"

template<typename T>
class BonusPool : public Pool<T>
{
public:
	BonusPool();
	void init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition);

private:
	void createNewObject() override;
	sf::Texture texture;
	sf::Vector2f initialPosition;
};

template<class T>
BonusPool<T>::BonusPool()
{
}

template<class T>
void BonusPool<T>::init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	this->texture = texture;
	this->initialPosition = initialPosition;

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
	obj.deactivate();
	Pool<T>::getPool().push_back(obj);
}