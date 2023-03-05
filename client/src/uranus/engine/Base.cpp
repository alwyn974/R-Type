/*
** EPITECH PROJECT, 2023
** Base.cpp
** File description:
** Base.cpp
*/

#include "uranus/engine/components/Base.hpp"
#include "uranus/engine/manager/Manager.hpp"

engine::Base::Base(const std::string &uniqueName)
{
    auto &r = engine::Manager::getRegistry();
    this->_entityId = r->spawnEntity();
    spdlog::info("created entity: {}", this->_entityId);
    this->_uniqueName = uniqueName;
}

const std::string &engine::Base::getUniqueName()
{
    return this->_uniqueName;
}

void engine::Base::setUniqueName(const std::string &uniqueName)
{
    _uniqueName = uniqueName;
}

void engine::Base::setEntityId(size_t entityId)
{
    _entityId = entityId;
}

size_t engine::Base::getEntityId()
{
    return this->_entityId;
}
