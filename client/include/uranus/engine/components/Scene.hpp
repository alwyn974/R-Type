/*
** EPITECH PROJECT, 2023
** Scene.hpp
** File description:
** Scene.hpp
*/

#ifndef URANUS_SCENE_HPP
#define URANUS_SCENE_HPP

#include "uranus/engine/Dependencies.hpp"
#include "Base.hpp"

namespace engine {

    class Scene {
    public:
        explicit Scene(const std::string &name);

        virtual ~Scene() = default;

        virtual void init() = 0;

        [[nodiscard]]
        const std::string &getName() const;

        void clear();

        void addPrefab(const std::shared_ptr<engine::Base> &prefab);

    private:
        std::string _name;
        std::vector<std::shared_ptr<engine::Base>> _entities;
    };
} // namespace engine

#endif // URANUS_SCENE_HPP
