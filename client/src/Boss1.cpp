/*
** EPITECH PROJECT, 2023
** Boss1.cpp
** File description:
** Boss1.cpp
*/

#include "Boss1.hpp"

Boss::Boss(const std::string &uniqueName, uranus::ecs::component::Position pos,
           std::shared_ptr<engine::Texture> &texture) : Enemy(uniqueName, pos, texture)
{
    this->_health = 300;

    auto &r = engine::Manager::getRegistry();
    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);

    r->addComponent(newEntity, uranus::ecs::component::Name{uniqueName});
    r->addComponent(newEntity, uranus::ecs::component::Position{pos.x, pos.y});
    r->addComponent(newEntity, uranus::ecs::component::Velocity{0, 0});
    r->addComponent(newEntity, uranus::ecs::component::Sprite{std::make_shared<engine::Sprite>(texture), 1});

    std::bitset<uranus::ecs::LAYER_MASK_SIZE> layer;
    layer.set(uranus::ecs::LayerMask::ENEMY);
    std::bitset<uranus::ecs::LAYER_MASK_SIZE> mask;
    mask.set(uranus::ecs::LayerMask::PLAYER_BULLET);
    r->addComponent(
            newEntity,
            uranus::ecs::component::Collisionable{
                    0, 0, 160, 215, layer, mask, [&](const size_t &entity, const size_t &entityCollidingWith) {
                        this->colliding(entity, entityCollidingWith);
                    }});
    r->addComponent(newEntity, uranus::ecs::component::Loop{[&](const size_t entity, float delta) { this->loop(entity, delta); }});

    r->addComponent(newEntity, uranus::ecs::component::Animation{
            4, 9, [&](const size_t entity, const std::string &animationName) {
                this->animationCallback(entity, animationName);
            }});

    engine::system::addNewAnimation(newEntity, "first", true, 0.4);
    engine::system::insertAnimationFrame(newEntity, "first", 0.0, 0);
    engine::system::insertAnimationFrame(newEntity, "first", 0.1, 1);
    engine::system::insertAnimationFrame(newEntity, "first", 0.2, 2);
    engine::system::insertAnimationFrame(newEntity, "first", 0.3, 3);

    engine::system::addNewAnimation(newEntity, "second", true, 0.4);
    engine::system::insertAnimationFrame(newEntity, "second", 0.0, 4);
    engine::system::insertAnimationFrame(newEntity, "second", 0.1, 5);
    engine::system::insertAnimationFrame(newEntity, "second", 0.2, 6);
    engine::system::insertAnimationFrame(newEntity, "second", 0.3, 7);

    engine::system::playAnimation(newEntity, "first");
}

void Boss::loop(size_t entity, float delta) {
    static auto &r = engine::Manager::getRegistry();
    if (r->getComponent<uranus::ecs::component::Position>(entity)->x < 800)
        return;
    auto &vel = r->getComponent<uranus::ecs::component::Velocity>(entity);
    vel->x = -50 * delta;
}

void Boss::colliding(const size_t &entity, const size_t &entityCollidingWith) {}

void Boss::animationCallback(size_t entity, const std::string &animationName) {
//    if (animationName == "first") {
//        spdlog::info("Playing first");
//        engine::system::playAnimation(entity, "second");
//    } else {
//        spdlog::info("Playing second");
//        engine::system::playAnimation(entity, "first");
//    }
}
