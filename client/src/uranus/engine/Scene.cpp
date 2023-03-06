/*
** EPITECH PROJECT, 2023
** Scene.cpp
** File description:
** Scene.cpp
*/

#include "uranus/engine/components/Scene.hpp"
#include "uranus/engine/manager/Manager.hpp"

engine::Scene::Scene(const std::string &name)
{
    this->_name = name;
}

const std::string &engine::Scene::getName() const
{
    return this->_name;
}

void engine::Scene::clear()
{
    static auto &entityManager = engine::Manager::getEntityManager();
    for (const auto &entity : this->_entities)
        entityManager->removePrefab(entity->getUniqueName());
    this->_entities.clear();
}

void engine::Scene::addPrefab(const std::shared_ptr<engine::Base> &prefab)
{
    static auto &entityManager = engine::Manager::getEntityManager();
    this->_entities.push_back(prefab);
    entityManager->addPrefab(prefab);
}
