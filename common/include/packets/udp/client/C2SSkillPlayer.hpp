/*
** EPITECH PROJECT, 2023
** C2SSkillPlayer.hpp
** File description:
** C2SSkillPlayer.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"
#include "C2SSkillEntity.hpp"

namespace rtype::network::packet {
    class KillEntityPacket : public C2SkillEntity {
    public:
        explicit KillEntityPacket(int id, int entity_id) : C2SkillEntity(entity_id)
        {
        }

        KillEntityPacket() : C2SkillEntity()
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SkillEntity::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SkillEntity::fromBytes(byteBuffer);
        }
    };
}