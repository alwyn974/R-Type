/*
** EPITECH PROJECT, 2023
** Base.hpp
** File description:
** Base.hpp
*/

#ifndef URANUS_BASE_HPP
#define URANUS_BASE_HPP

#include "uranus/ecs/Entity.hpp"
#include "uranus/engine/Dependencies.hpp"

namespace engine {
    class Base {
    public:
        virtual ~Base() = default;

        explicit Base(const std::string &uniqueName);

        const std::string &getUniqueName();

        size_t getEntityId();

        void setUniqueName(const std::string &uniqueName);

        void setEntityId(size_t entityId);

    protected:
        std::string _uniqueName;
        size_t _entityId;
    };
} // namespace engine

#endif // URANUS_BASE_HPP
