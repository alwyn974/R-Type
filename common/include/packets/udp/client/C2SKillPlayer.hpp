/*
** EPITECH PROJECT, 2023
** C2SSkillPlayer.hpp
** File description:
** C2SSkillPlayer.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>
#include "C2SKillEntity.hpp"

namespace rtype::network::packet {
    class C2SKillPlayer : public C2SKillEntity {
    public:
        explicit C2SKillPlayer(int id, int entityId) : C2SKillEntity(entityId) {}

        C2SKillPlayer() : C2SKillEntity() {}

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SKillEntity::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SKillEntity::fromBytes(byteBuffer);
        }
    };
}