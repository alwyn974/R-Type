/*
** EPITECH PROJECT, 2023
** EntityManager.cpp
** File description:
** EntityManager.cpp
*/

#include "uranus/engine/manager/EntityManager.hpp"
#include "uranus/engine/manager/Manager.hpp"
#include "uranus/ecs/Components.hpp"

void engine::EntityManager::addPrefab(const std::shared_ptr<engine::Base> &prefab)
{
    std::string name = prefab->getUniqueName();
    if (this->_prefabs.contains(prefab->getUniqueName())) {
        name = name + std::to_string(this->_globalId++);
        prefab->setUniqueName(name);
    }
        //throw uranus::ex::Exception("Prefab already exist");
//    spdlog::info("prefab: {}", name);
    this->_prefabs[name] = prefab;
}

std::shared_ptr<engine::Base> engine::EntityManager::getPrefabByName(const std::string &prefabName)
{
    if (!this->_prefabs.contains(prefabName))
        throw uranus::ex::Exception("Prefab not found");
    return this->_prefabs[prefabName];
}

std::shared_ptr<engine::Base> engine::EntityManager::getPrefabByNetworkId(std::uint32_t networkId)
{
    for (const auto &[name, prefab] : this->_prefabs) {
        auto &r = engine::Manager::getRegistry();
        auto &id = r->getComponent<uranus::ecs::component::NetworkId>(prefab->getEntityId());
        if (id && id->uniqueId == networkId)
            return prefab;
    }

    throw uranus::ex::Exception("Prefab not found");
}

bool engine::EntityManager::removePrefab(const std::string &prefabName)
{
    if (!this->_prefabs.contains(prefabName))
        return false;
    this->_prefabs.erase(prefabName);
    return true;
}

void engine::EntityManager::killAllPrefabs()
{
    this->_prefabs.clear();
}

bool engine::EntityManager::removeByNetworkId(std::uint32_t networkId)
{
    for (const auto &[name, prefab] : this->_prefabs) { // NOLINT
        auto &r = engine::Manager::getRegistry();
        auto &id = r->getComponent<uranus::ecs::component::NetworkId>(prefab->getEntityId());
        if (id && id->uniqueId == networkId) {
            this->_prefabs.erase(name);
            return true;
        }
    }
    return false;
}

std::shared_ptr<engine::Base> engine::EntityManager::getPrefabByEntityId(std::size_t entityId)
{
    for (const auto &[name, prefab] : this->_prefabs) {
        if (prefab->getEntityId() == entityId)
            return prefab;
    }
    throw uranus::ex::Exception("Prefab not found");
}

