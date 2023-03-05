/*
** EPITECH PROJECT, 2023
** EntityManager.hpp
** File description:
** EntityManager.hpp
*/

#ifndef URANUS_ENTITYMANAGER_HPP
#define URANUS_ENTITYMANAGER_HPP

#include "uranus/engine/components/Base.hpp"
#include <map>

namespace engine {
    class EntityManager {
    public:
        EntityManager() { this->_globalId = 0; };

        ~EntityManager() = default;

        void addPrefab(const std::shared_ptr<engine::Base> &prefab);

        void killAllPrefabs();

        std::shared_ptr<engine::Base> getPrefabByName(const std::string &prefabName);

        bool removePrefab(const std::string &prefabName);

    private:
        std::map<std::string, std::shared_ptr<engine::Base>> _prefabs;
        int _globalId;

    };
} // namespace engine

#endif // URANUS_ENTITYMANAGER_HPP
