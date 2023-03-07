//
// Created by Nico on 05/03/2023.
//

#include "ParallaxLayer.hpp"

void ParallaxLayer::loop(size_t entity, float delta) {
    auto &r = engine::Manager::getRegistry();
    auto &sprite = r->getComponent<uranus::ecs::component::Sprite>(entity);
    auto &rect = sprite->sprite->getTextureRect();
    sprite->sprite->setTextureRect({static_cast<int>(rect.left + this->_speed * delta), rect.top, rect.width, rect.height});
}

ParallaxLayer::ParallaxLayer(std::string &name, std::shared_ptr<engine::Texture> &texture, float speed) : Base(name) {
    auto &r = engine::Manager::getRegistry();
    const uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);
    this->_speed = speed;
    texture->setRepeated(true);
    auto sprite = std::make_shared<engine::Sprite>(texture);
    sprite->setTextureRect({0, 0, WIN_WIDTH, WIN_HEIGHT});
    const sf::Vector2f scale = {(float)(WIN_WIDTH) / (float) texture->getSize().x, ((float) (WIN_HEIGHT) / (float) texture->getSize().y)}; // NOLINT
    sprite->setScale(scale);
    r->addComponent(newEntity, uranus::ecs::component::Position{0, 0});
    r->addComponent(newEntity, uranus::ecs::component::Name{name});
    r->addComponent(newEntity, uranus::ecs::component::Sprite{sprite});
    r->addComponent(newEntity, uranus::ecs::component::Loop{
            [&](size_t entity, float delta) {
                this->loop(entity, delta);
            }
    });
}
