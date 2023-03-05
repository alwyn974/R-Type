//
// Created by Nico on 05/03/2023.
//

#include "ParallaxLayer.hpp"

void ParallaxLayer::loop(size_t entity) {
    auto &r = engine::Manager::getRegistry();
    auto &sprite = r->getComponent<uranus::ecs::component::Sprite>(entity);
    auto &rect = sprite->sprite->getTextureRect();
    sprite->sprite->setTextureRect({static_cast<int>(rect.left + this->_speed), rect.top, rect.width, rect.height});
}

ParallaxLayer::ParallaxLayer(std::string &name, std::shared_ptr<engine::Texture> &texture, float speed) : Base(name) {
    auto &r = engine::Manager::getRegistry();
    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);
    this->_speed = speed;
    texture->setRepeated(true);
    auto sprite = std::make_shared<engine::Sprite>(texture);
    sprite->setTextureRect({0, 0, 1280, 720});
    sf::Vector2f scale = {static_cast<float>(1280.0 / texture->getSize().x),
                          static_cast<float>(720.0 / texture->getSize().y)};
    sprite->setScale(scale);
    r->addComponent(newEntity, uranus::ecs::component::Position{0, 0});
    r->addComponent(newEntity, uranus::ecs::component::Name{name});
    r->addComponent(newEntity, uranus::ecs::component::Sprite{sprite});
    r->addComponent(newEntity, uranus::ecs::component::Loop{
            [&](size_t entity) {
                this->loop(entity);
            }
    });
}
