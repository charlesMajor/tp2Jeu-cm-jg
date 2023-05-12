#pragma once
#include "stdafx.h"
#include "Pool.h"

template<typename T>
class EnemyPool : public Pool<T>
{
public:
	EnemyPool();
	void init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition);

private:
	void createNewObject() override;
	sf::Texture texture;
	sf::Vector2f initialPosition;
};

template<class T>
EnemyPool<T>::EnemyPool()
{
}

template<class T>
void EnemyPool<T>::init(int nbObject, const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	this->texture = texture;
	this->initialPosition = initialPosition;

	for (int i = 0; i < nbObject; i++)
	{
		this->createNewObject();
	}
}

template<class T>
void EnemyPool<T>::createNewObject()
{
	T obj;
	obj.initialize(texture, initialPosition);
	obj.deactivate();
	Pool<T>::getPool().push_back(obj);
}