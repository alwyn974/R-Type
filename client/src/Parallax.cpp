/*
** EPITECH PROJECT, 2023
** Parallax.cpp
** File description:
** Parallax.cpp
*/

#include "Parallax.hpp"
#include "ParallaxLayer.hpp"

Parallax::Parallax(const std::string &uniqueName1, std::vector<std::string> &names) : Base(uniqueName1) {
    auto &textureManager = engine::Manager::getTextureManager();
    auto &r = engine::Manager::getRegistry();
//    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);
    auto &entityManager = engine::Manager::getEntityManager();

    float speed = 1.0;
    for (auto &name: names) {
//        textureManager->addTexture(name, name);
//        r->addComponent(newEntity, uranus::ecs::component::Sprite{
//                std::make_shared<engine::Sprite>(textureManager->getTextureByName(name))});
        auto layer = std::make_shared<ParallaxLayer>(name, textureManager->getTextureByName(name), speed);
        entityManager->addPrefab(layer);
        speed++;
    }
}
