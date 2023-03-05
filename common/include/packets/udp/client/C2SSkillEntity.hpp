/*
** EPITECH PROJECT, 2023
** C2SSkillEntity.hpp
** File description:
** C2SSkillEntity.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class C2SSkillEntity : public sa::AbstractPacket {
    public:
        int entity_id;

        explicit C2SSkillEntity(int entity_id) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entity_id = entity_id;
        }

        C2SSkillEntity() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeInt(entity_id);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entity_id = byteBuffer.readInt();
        }
    };
}