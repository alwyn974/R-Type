/*
** EPITECH PROJECT, 2023
** Player.cpp
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "Bullet.hpp"
#include "network/NetworkManager.hpp"

Player::Player(const std::string &uniqueName, std::shared_ptr<engine::Texture> &texture, const std::string &bulletTextureName, const sf::Vector2f &pos, bool network) : Base(uniqueName)
{
    this->_bulletTextureName = bulletTextureName;
    this->_doubleBullet = false;
    this->_networked = network;

    auto &r = engine::Manager::getRegistry();
    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);

    r->addComponent(newEntity, uranus::ecs::component::Name {uniqueName});
    r->addComponent(newEntity, uranus::ecs::component::Position {pos.x, pos.y});
    r->addComponent(newEntity, uranus::ecs::component::Velocity {0, 0});
    r->addComponent(newEntity, uranus::ecs::component::Sprite {std::make_shared<engine::Sprite>(texture)});
    if (!this->_networked)
        r->addComponent(newEntity, uranus::ecs::component::InputKeyboard {[&](size_t entity, const engine::Event event) { this->move(entity, event); }});

    std::bitset<uranus::ecs::LAYER_MASK_SIZE> layer;
    layer.set(uranus::ecs::LayerMask::PLAYER);
    std::bitset<uranus::ecs::LAYER_MASK_SIZE> mask;
    mask.set(uranus::ecs::LayerMask::ENEMY);
    mask.set(uranus::ecs::LayerMask::ENEMY_BULLET);
    mask.set(uranus::ecs::LayerMask::BONUS);
    r->addComponent(
        newEntity,
        uranus::ecs::component::Collisionable {
            0, 0, 30, 15, layer, mask, [&](const size_t &entity, const size_t &entityCollidingWith) { this->colliding(entity, entityCollidingWith); }});
}

void Player::move(size_t entity, const engine::Event event)
{
    auto &r = engine::Manager::getRegistry();
    auto &vel = r->getComponent<uranus::ecs::component::Velocity>(entity);
    auto &pos = r->getComponent<uranus::ecs::component::Position>(entity);
    const int speed = 2;
    if (vel) {
        if (engine::Keyboard::isKeyPressed(engine::Keyboard::Key::Q)) {
            vel->x = -speed;
        } else if (engine::Keyboard::isKeyPressed(engine::Keyboard::Key::D)) {
            vel->x = speed;
        } else {
            vel->x = 0;
        }
        if (engine::Keyboard::isKeyPressed(engine::Keyboard::Key::Z)) {
            vel->y = -speed;
        } else if (engine::Keyboard::isKeyPressed(engine::Keyboard::Key::S)) {
            vel->y = speed;
        } else {
            vel->y = 0;
        }
    }
    if (pos) {
        if (event.mouseButton.button == sf::Mouse::Left && event.type == event.MouseButtonPressed) {
            this->shoot();
        }
    }
}

void Player::colliding(const size_t &entity, const size_t &entityCollidingWith) {}

void Player::enableDoubleBullet()
{
    this->_doubleBullet = true;
}

void Player::shoot()
{
    auto &r = engine::Manager::getRegistry();
    auto &textureManager = engine::Manager::getTextureManager();
    auto &entityManager = engine::Manager::getEntityManager();

    auto &pos = r->getComponent<uranus::ecs::component::Position>(this->_entityId);
    auto &networkManager = rtype::client::network::NetworkManager::getInstance();

    if (this->_doubleBullet) {
        auto bullet = std::make_shared<Bullet>(
            "bullet", uranus::ecs::component::Position {pos->x + 30, pos->y + 10}, textureManager->getTextureByName(this->_bulletTextureName));
        entityManager->addPrefab(bullet);
        auto bullet2 = std::make_shared<Bullet>(
            "bullet", uranus::ecs::component::Position {pos->x + 30, pos->y - 10}, textureManager->getTextureByName(this->_bulletTextureName));
        entityManager->addPrefab(bullet2);
    } else {
        const sf::Vector2f position { pos->x, pos->y };
        auto bullet = std::make_shared<Bullet>(
            "bullet", uranus::ecs::component::Position {position.x + 30, position.y}, textureManager->getTextureByName(this->_bulletTextureName));
        networkManager->send(std::make_shared<rtype::network::packet::C2SPlayerShoot>(position.x, position.y));
        entityManager->addPrefab(bullet);
    }
}
