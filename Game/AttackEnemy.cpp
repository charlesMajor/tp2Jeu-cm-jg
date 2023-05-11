#include "stdafx.h"
#include "AttackEnemy.h"
#include "game.h"
#include "GameScene.h"

const int AttackEnemy::BASE_HEALTH = 2;
const int AttackEnemy::MAX_RECOIL = 120;

AttackEnemy::AttackEnemy()
    : Enemy()
    , health(BASE_HEALTH)
{
}

AttackEnemy::AttackEnemy(const AttackEnemy& src)
    : Enemy(src)
{
    health = src.health;
}

void AttackEnemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    GameObject::initialize(texture, initialPosition);
}

bool AttackEnemy::update(float elapsedTime, sf::Vector2f playerPosition)
{
    recoil = std::max(0, recoil - 1);
    Enemy::update(elapsedTime);
    if ((getPosition().x - playerPosition.x) * (getPosition().x - playerPosition.x) < 2 && recoil == 0)
    {
        recoil = MAX_RECOIL;
        return true;
    }
    return false;
}

void AttackEnemy::activate()
{
    if (getPosition().y == GameScene::ATTACK_ENEMIES_Y_POSITION)
    {
        Enemy::activate(true, 70);
    }
    else
    {
        Enemy::activate(false, 70);
    }   
}

void AttackEnemy::onHit()
{
    health--;
    if (health <= 0)
    {
        this->onDeath();
    }
}

int AttackEnemy::getAngleForBullet()
{
    return bulletAngle;
}