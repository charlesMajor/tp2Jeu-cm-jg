#pragma once
#include "stdafx.h"

template<typename T>
class Pool
{
public:
	Pool();
	void draw(sf::RenderWindow& window) const;

	T& getAvaiableObject();
	std::list<T>& getPool();

private:
	std::list<T> poolList;

	virtual void createNewObject() = 0;
};

template<class T>
Pool<T>::Pool()
{
}

template<class T>
void Pool<T>::draw(sf::RenderWindow& window) const
{
	for (const auto& obj : poolList)
	{
		if (obj.isActive())
			obj.draw(window);
	}
}

template<class T>
T& Pool<T>::getAvaiableObject()
{
	for (auto& obj : poolList)
	{
		if (!obj.isActive())
			return obj;
	}
	this->createNewObject();
	return poolList.back();
}

template<class T>
std::list<T>& Pool<T>::getPool()
{
	return poolList;
}