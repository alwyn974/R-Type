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

        std::shared_ptr<engine::Base> getPrefabByNetworkId(std::uint32_t networkId);

        std::shared_ptr<engine::Base> getPrefabByEntityId(std::size_t entityId);

        bool removePrefab(const std::string &prefabName);

        bool removeByNetworkId(std::uint32_t networkId);

    private:
        std::map<std::string, std::shared_ptr<engine::Base>> _prefabs;
        int _globalId;

    };
} // namespace engine

#endif // URANUS_ENTITYMANAGER_HPP
