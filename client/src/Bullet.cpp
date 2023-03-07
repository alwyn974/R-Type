/*
** EPITECH PROJECT, 2023
** Bullet.cpp
** File description:
** Bullet.cpp
*/

#include "Bullet.hpp"
#include "Explosion.hpp"
#include "network/NetworkManager.hpp"

Bullet::Bullet(const std::string &uniqueName, uranus::ecs::component::Position pos, std::shared_ptr<engine::Texture> &texture, std::uint32_t networkId, bool owned) : Base(uniqueName)
{
    this->canMove = false;
    this->networkId = networkId;
    this->networked = networkId > 0 && !owned;
    this->sent = false;

    auto &r = engine::Manager::getRegistry();
    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);

    if (networkId > 0)
        r->addComponent(newEntity, uranus::ecs::component::NetworkId {networkId});

    r->addComponent(newEntity, uranus::ecs::component::Name {uniqueName});
    r->addComponent(newEntity, uranus::ecs::component::Position {pos.x, pos.y});
    r->addComponent(newEntity, uranus::ecs::component::Velocity {0, 0});
    r->addComponent(newEntity, uranus::ecs::component::Sprite {std::make_shared<engine::Sprite>(texture), 1});

    std::bitset<uranus::ecs::LAYER_MASK_SIZE> layer;
    layer.set(uranus::ecs::LayerMask::PLAYER_BULLET);
    std::bitset<uranus::ecs::LAYER_MASK_SIZE> mask;
    mask.set(uranus::ecs::LayerMask::ENEMY);
    r->addComponent(
        newEntity,
        uranus::ecs::component::Collisionable {
            0, 0, 22, 20, layer, mask, [&](const size_t &entity, const size_t &entityCollidingWith) { this->colliding(entity, entityCollidingWith); }});
    r->addComponent(newEntity, uranus::ecs::component::Loop {[&](const size_t entity) { this->loop(entity); }});
    if (!this->networked)
        r->addComponent(newEntity, uranus::ecs::component::InputKeyboard {[&](size_t entity, const engine::Event event) { this->handleKeyboard(entity, event); }});

    r->addComponent(newEntity, uranus::ecs::component::Animation {3, 1, [&](const size_t entity, const std::string &animationName) { return; }});
    engine::system::addNewAnimation(newEntity, "charge", false, 3);
    engine::system::insertAnimationFrame(newEntity, "charge", 0.0, 0);
    engine::system::insertAnimationFrame(newEntity, "charge", 1, 1);
    engine::system::insertAnimationFrame(newEntity, "charge", 2, 2);

    engine::system::playAnimation(newEntity, "charge");
}

void Bullet::move(size_t entity)
{
    static auto &r = engine::Manager::getRegistry();
    auto &vel = r->getComponent<uranus::ecs::component::Velocity>(entity);
    vel->x = 5;
    if (r->getComponent<uranus::ecs::component::Position>(entity)->x > WIN_WIDTH + 20) {
//        r->killEntity(entity);
        auto ent = r->entityFromIndex(entity);
        r->addComponent(ent, uranus::ecs::component::Dead());
    }
}

void Bullet::loop(const size_t entity)
{
    if (!this->canMove) return;
//    auto &r = engine::Manager::getRegistry();
    this->move(entity);
}

void Bullet::colliding(const size_t &entity, const size_t &entityCollidingWith)
{
    //    std::cout << entity << ", " << entityCollidingWith << std::endl;
    static auto &r = engine::Manager::getRegistry();
    static auto &entityManager = engine::Manager::getEntityManager();
    static auto &textureManager = engine::Manager::getTextureManager();

    auto pos = r->getComponent<uranus::ecs::component::Position>(entityCollidingWith);

    auto explosion = std::make_shared<Explosion>("explosion", uranus::ecs::component::Position {pos->x, pos->y}, textureManager->getTextureByName("explosion"));
    entityManager->addPrefab(explosion);

    auto ent1 = r->entityFromIndex(entity);
    auto ent2 = r->entityFromIndex(entityCollidingWith);
    r->addComponent(ent1, uranus::ecs::component::Dead());
    r->addComponent(ent2, uranus::ecs::component::Dead());
}

void Bullet::handleKeyboard(size_t entity, const engine::Event event)
{
    static auto &networkManager = rtype::client::network::NetworkManager::getInstance();
    static auto &r = engine::Manager::getRegistry();

    if (this->canMove) return;
    if (event.type == event.MouseButtonReleased && !this->sent) {
        this->canMove = true;
//        engine::system::stopAnimation(this->_entityId);
        auto pos = r->getComponent<uranus::ecs::component::Position>(entity);
//        networkManager->send(std::make_shared<rtype::network::packet::C2SPlayerShoot>(this->networkId, pos->x, pos->y));
        this->sent = true;
    }
}

bool Bullet::isCanMove() const
{
    return canMove;
}

void Bullet::setCanMove(bool move)
{
    this->canMove = move;
    engine::system::stopAnimation(this->_entityId);
}
