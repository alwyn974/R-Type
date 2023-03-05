/*
** EPITECH PROJECT, 2023
** EntityManager.cpp
** File description:
** EntityManager.cpp
*/

#include "uranus/engine/manager/EntityManager.hpp"

//void engine::EntityManager::addPrefab(const std::shared_ptr<engine::Base> &prefab)
//{
//    this->_prefabs.push_back(prefab);
//}
//
//std::shared_ptr<engine::Base> engine::EntityManager::getPrefabByName(const std::string &prefabName)
//{
//    for (const std::shared_ptr<engine::Base> &prefab : this->_prefabs) {
//        if (prefab->getUniqueName() == prefabName) {
//            return prefab;
//        }
//    }
//}
//
//void engine::EntityManager::killAllPrefabs()
//{
//    this->_prefabs.clear();
//}

void engine::EntityManager::addPrefab(const std::shared_ptr<engine::Base> &prefab)
{
    std::string name = prefab->getUniqueName();
    if (this->_prefabs.contains(prefab->getUniqueName()))
        name = name + std::to_string(GLOBAL_ID++);
        //throw uranus::ex::Exception("Prefab already exist");
    this->_prefabs[name] = prefab;
}

std::shared_ptr<engine::Base> engine::EntityManager::getPrefabByName(const std::string &prefabName)
{
    if (!this->_prefabs.contains(prefabName))
        throw uranus::ex::Exception("Prefab not found");
    return this->_prefabs[prefabName];
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