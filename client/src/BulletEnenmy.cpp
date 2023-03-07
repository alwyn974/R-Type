/*
** EPITECH PROJECT, 2023
** BulletEnenmy.cpp
** File description:
** BulletEnenmy.cpp
*/

#include "BulletEnemy.hpp"

BulletEnemy::BulletEnemy(const std::string &uniqueName, uranus::ecs::component::Position pos, std::shared_ptr<engine::Texture> &texture) :
    Bullet(uniqueName, pos, texture)
{
    std::bitset<uranus::ecs::LAYER_MASK_SIZE> layer;
    layer.set(uranus::ecs::LayerMask::ENEMY_BULLET);
    std::bitset<uranus::ecs::LAYER_MASK_SIZE> mask;
    mask.set(uranus::ecs::LayerMask::PLAYER);
    engine::system::setLayer(this->_entityId, layer);
    engine::system::setMask(this->_entityId, mask);
    this->canMove = true;
    engine::system::stopAnimation(this->_entityId);
}

void BulletEnemy::move(size_t entity)
{
    auto &r = engine::Manager::getRegistry();
    auto &vel = r->getComponent<uranus::ecs::component::Velocity>(entity);
    vel->x = -5;
    if (r->getComponent<uranus::ecs::component::Position>(entity)->x < -100) {
        r->killEntity(entity);
    }
}
