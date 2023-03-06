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
    class C2SSkillPlayer : public C2SSkillEntity {
    public:
        explicit C2SSkillPlayer(int id, int entity_id) : C2SSkillEntity(entity_id)
        {
        }

        C2SSkillPlayer() : C2SSkillEntity()
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SSkillEntity::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            C2SSkillEntity::fromBytes(byteBuffer);
        }
    };
}